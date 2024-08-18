#ifndef UTILS_TIMESTAMP_H_
#define UTILS_TIMESTAMP_H_

#include <chrono>
#include <string>

#include <sstream>
#include <ctime>
#include <iomanip>

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

inline std::string timestamp1() {
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

inline std::string timestamp2() {
    // Get the current time point
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm gmt{};
    gmtime_r(&now_time_t, &gmt);

    // Calculate fractional seconds
    auto duration = now.time_since_epoch();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    auto fractional_seconds = std::chrono::duration_cast<std::chrono::microseconds>(duration - seconds).count();

    // Create a char buffer for the timestamp string
    char buffer[32]; // Large enough to hold the formatted string

    // Format the string using snprintf
    int n = snprintf(buffer, sizeof(buffer), "%04d/%02d/%02d %02d:%02d:%09.6f",
                     gmt.tm_year + 1900, gmt.tm_mon + 1, gmt.tm_mday, gmt.tm_hour,
                     gmt.tm_min, fractional_seconds / 1000000.0);

    // Return the formatted string as std::string
    return std::string(buffer, n); // Use the exact number of characters written
}

#endif