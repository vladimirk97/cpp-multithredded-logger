#include <gtest/gtest.h>

#include "utils/timestamp.h"

#include <regex>

TEST(TimestampTest, FormatValidation)
{
    std::string ts = MTLogger::timestamp();

    // Define a regex to validate the format: YYYY/MM/DD HH:MM:SS.microseconds
    std::regex ts_regex(R"(\d{4}/\d{2}/\d{2} \d{2}:\d{2}:\d{2}\.\d{6})");

    // Check if the timestamp matches the expected format
    ASSERT_TRUE(std::regex_match(ts, ts_regex)) << "Timestamp format does not match expected format: " << ts;
}
