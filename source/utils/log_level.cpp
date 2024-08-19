#include "utils/log_level.h"

namespace MTLogger
{
namespace LogLevel
{

struct enum_hasher
{
    template<typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

const std::unordered_map<Level, std::string, enum_hasher> log_level_out 
{
    {Level::DEBUG, " [DEBUG] "}, 
    {Level::INFO,  " [INFO] "}, 
    {Level::WARN,  " [WARN] "}, 
    {Level::ERROR, " [ERROR] "}, 
    {Level::FATAL, " [FATAL] "},
};

std::string get_level(Level level)
{
    return log_level_out.find(level)->second;
}

} // namespace LogLevel
} // namespace MTLogger