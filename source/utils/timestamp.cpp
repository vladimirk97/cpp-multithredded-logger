#ifndef UTILS_TIMESTAMP_H_
#define UTILS_TIMESTAMP_H_

#include <chrono>
#include <string>

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

#endif