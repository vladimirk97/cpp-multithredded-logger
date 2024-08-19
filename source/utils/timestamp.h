#ifndef UTILS_TIMESTAMP_H_
#define UTILS_TIMESTAMP_H_

#include <chrono>
#include <string>

#include <sstream>
#include <ctime>
#include <iomanip>

namespace MTLogger
{

inline std::string timestamp() {
    // Get the current time point
    auto now = std::chrono::system_clock::now();
    
    // Convert to time_t to extract calendar time
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm gmt{};
    gmtime_r(&now_time_t, &gmt);

    // Calculate fractional seconds
    auto duration = now.time_since_epoch();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    auto fractional_seconds = std::chrono::duration_cast<std::chrono::microseconds>(duration - seconds).count();

    // Format the timestamp string
    std::ostringstream oss;
    oss << std::put_time(&gmt, "%Y/%m/%d %H:%M:%S");
    oss << '.' << std::setw(6) << std::setfill('0') << fractional_seconds;

    return oss.str();
}

} // MTLogger

#endif