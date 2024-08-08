#ifndef MULTITHREDED_LOGGER_HPP_
#define MULTITHREDED_LOGGER_HPP_

#include "thread_safe_queue.hpp"

#include <atomic>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <queue>
#include <string>

namespace MTLogger
{
    template<typename T>
    class Logger
    {
    private:
        TSQueue<T> m_ts_queue;

    public:
        Logger();
        ~Logger();

        /* \brief Deleted copy constructor */
        Logger(const Logger&) = delete;

        /* \brief Deleted move constructor */
        Logger(Logger&&) = delete;
        
        /* \brief Deleted copy assign operator */
        Logger& operator=(const Logger&) = delete;
        
        /* \brief Deleted move assign operator */
        Logger& operator=(Logger&&) = delete;

        void log(std::string record);
        
        void receiver(void);
    };

    template<typename T>
    Logger<T>::Logger(/* args */)
    {
    }
    
    template<typename T>
    Logger<T>::~Logger()
    {
    
    }
    
    void Logger::log(std::string record) 
    {

    }

} // namespace MTLogger


#endif /* MULTITHREDED_LOGGER_HPP_ */