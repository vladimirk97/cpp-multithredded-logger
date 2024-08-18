#ifndef UTILS_LOG_LEVEL_H_
#define UTILS_LOG_LEVEL_H_

#include <cstddef>
#include <unordered_map>
#include <string>

namespace LogLevel
{
    enum class Level
    {
        DEBUG, INFO, WARN, ERROR, FATAL
    };

    std::string get_level(Level level);
     
} // namespace LogLevel

#endif // UTILS_LOG_LEVEL_H_