#ifndef MULTITHREDED_LOGGER_HPP_
#define MULTITHREDED_LOGGER_HPP_

#include "thread_safe_queue.hpp"

#include <string>
#include <thread>
#include <fstream>
#include <atomic>
#include <unordered_map>

namespace MTLogger {

    enum class LogLevel {
        DEBUG, INFO, WARN, ERROR, FATAL
    };

    struct enum_hasher {
        template<typename T>
        std::size_t operator()(T t) const {
            return static_cast<std::size_t>(t);
        }
    };

    const std::unordered_map<LogLevel, std::string, enum_hasher> log_level_out 
    {
        {LogLevel::DEBUG, " [DEBUG] "}, 
        {LogLevel::INFO,  " [INFO] "}, 
        {LogLevel::WARN,  " [WARN] "}, 
        {LogLevel::ERROR, " [ERROR] "}, 
        {LogLevel::FATAL, " [FATAL] "},
    };

    inline std::string timestamp() {
        //get the time
        std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
        std::time_t tt = std::chrono::system_clock::to_time_t(tp);
        std::tm gmt{}; gmtime_r(&tt, &gmt);
        std::chrono::duration<double> fractional_seconds =
        (tp - std::chrono::system_clock::from_time_t(tt)) + std::chrono::seconds(gmt.tm_sec);
        //format the string
        std::string buffer("year/mo/dy hr:mn:sc.xxxxxx0");
        snprintf(&buffer.front(), buffer.length(), "%04d/%02d/%02d %02d:%02d:%09.6f",
                gmt.tm_year + 1900, gmt.tm_mon + 1, gmt.tm_mday, gmt.tm_hour, gmt.tm_min,
                fractional_seconds.count());
        //remove trailing null terminator added by snprintf
        buffer.pop_back();
        return buffer;
    }

    class Logger {
      private:
        TSQueue<std::string> m_ts_queue;
        std::thread m_receiver_thread;
        std::atomic<bool> m_shut_down;

        std::ofstream m_file;
        std::string m_filepath;

      protected:
        Logger(std::string filepath);
        
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
        void log(const std::string record, LogLevel level);

        static Logger& get_logger(void) ;
    };

    Logger::Logger(std::string filepath): m_filepath(filepath) {
        try {
            m_file.open(m_filepath, std::ofstream::app);
        } 
        catch(std::exception& e) {
            try {
                m_file.close();
            }
            catch(...) {}
            throw(e);
        }

        m_shut_down.store(false);
        m_receiver_thread = std::thread(&Logger::receiver, this);
    }
    
    Logger::~Logger() {
        m_shut_down.store(true);
        m_ts_queue.shutdown();
        m_receiver_thread.join(); 
    }
    
    void Logger::log(const std::string record, LogLevel level) {
        std::string output;
        output.append(timestamp());
        output.append(log_level_out.find(level)->second);
        output.append(record);
        m_ts_queue.push(output);
    }

    void Logger::receiver(void) {
        while(!m_shut_down.load() || !m_ts_queue.empty()) {
            std::unique_ptr<std::string> data = m_ts_queue.pop();
            if(data) {
                m_file << *data << "\n";
                m_file.flush();
            }
        }
    }

    Logger& Logger::get_logger(void) {
        static Logger logger("/home/vlada/Projects/vlada/cpp-multithredded-logger/logs/test1.txt");
        return logger;
    }

    inline void DEBUG(const std::string data) {
        Logger::get_logger().log(data, LogLevel::DEBUG);
    }
    inline void INFO(const std::string data) {
        Logger::get_logger().log(data, LogLevel::INFO);
    }
    inline void WARN(const std::string data) {
        Logger::get_logger().log(data, LogLevel::WARN);
    }
    inline void ERROR(const std::string data) {
        Logger::get_logger().log(data, LogLevel::ERROR);
    }
    inline void FATAL(const std::string data) {
        Logger::get_logger().log(data, LogLevel::FATAL);
    }
} // namespace MTLogger

#endif /* MULTITHREDED_LOGGER_HPP_ */