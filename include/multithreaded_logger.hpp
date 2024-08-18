#ifndef MULTITHREADED_LOGGER_HPP_
#define MULTITHREADED_LOGGER_HPP_

#include "thread_safe_queue.hpp"

#include "interfaces/log_writer.h"
#include "utils/log_level.h"
#include "utils/record.h"

#include <string>
#include <thread>
#include <fstream>
#include <atomic>
#include <unordered_map>

namespace MTLogger {
    class Logger {
      private:
        TSQ::ThreadSafeQueue<std::unique_ptr<LogRecord>> m_ts_queue;
        std::unique_ptr<LogWriter> m_log_writer;

        std::thread m_receiver_thread;
        std::atomic<bool> m_shut_down;

        // std::ofstream m_file;
        // std::string m_filepath;

      protected:
        Logger(std::unique_ptr<LogWriter> log_writer);
        
        ~Logger();
      
        /* \brief Worker that receives log records from the queue and writes them to a file */
        void receiver(void);

      public:
        /* \brief Deleted copy constructor */
        Logger(const Logger&) = delete;

        /* \brief Deleted move constructor */
        Logger(Logger&&) = delete;
        
        /* \brief Deleted copy assign operator */
        Logger& operator=(const Logger&) = delete;
        
        /* \brief Deleted move assign operator */
        Logger& operator=(Logger&&) = delete;

        /* \brief Add log record to the queue */
        void log(const std::string record, LogLevel::Level level);

        static Logger& get_logger(void) ;
    };

    Logger::Logger(std::unique_ptr<LogWriter> log_writer): m_log_writer(std::move(log_writer)) 
    {
        m_shut_down.store(false);
        m_receiver_thread = std::thread(&Logger::receiver, this);
    }
    
    Logger::~Logger() 
    {
        m_shut_down.store(true);
        m_ts_queue.shutdown(true);
        m_receiver_thread.join(); 
    }
    
    void Logger::log(const std::string record, LogLevel::Level level) 
    {
        std::unique_ptr<LogRecord> data = std::make_unique<LogRecord>();
        data->record = record;
        data->severity_level = level;
        m_ts_queue.push(data);
    }

    void Logger::receiver(void) 
    {
        while(!m_shut_down.load() || !m_ts_queue.empty()) 
        {
            std::unique_ptr<LogRecord> data; 
            bool status = m_ts_queue.pop(data);
            if(status) 
            {
                m_log_writer->write_log(data->severity_level, data->record);
                // m_file << data << "\n";
                // m_file.flush();
            }
        }
    }

    Logger& Logger::get_logger(void) {
        static Logger logger(std::move(std::make_unique<LogWriter>()));
        return logger;
    }

    inline void DEBUG(const std::string data) {
        Logger::get_logger().log(data, LogLevel::Level::DEBUG);
    }
    inline void INFO(const std::string data) {
        Logger::get_logger().log(data, LogLevel::Level::INFO);
    }
    inline void WARN(const std::string data) {
        Logger::get_logger().log(data, LogLevel::Level::WARN);
    }
    inline void ERROR(const std::string data) {
        Logger::get_logger().log(data, LogLevel::Level::ERROR);
    }
    inline void FATAL(const std::string data) {
        Logger::get_logger().log(data, LogLevel::Level::FATAL);
    }
} // namespace MTLogger

#endif /* MULTITHREADED_LOGGER_HPP_ */