#include <gtest/gtest.h>

#include "utils/log_level.h"

TEST(LogLevel, GetLevelString) 
{
    using namespace MTLogger;
    
    EXPECT_EQ(LogLevel::get_level(LogLevel::Level::DEBUG), " [DEBUG] ");
    EXPECT_EQ(LogLevel::get_level(LogLevel::Level::INFO), " [INFO] ");
    EXPECT_EQ(LogLevel::get_level(LogLevel::Level::WARN), " [WARN] ");
    EXPECT_EQ(LogLevel::get_level(LogLevel::Level::ERROR), " [ERROR] ");
    EXPECT_EQ(LogLevel::get_level(LogLevel::Level::FATAL), " [FATAL] ");
}