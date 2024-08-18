#include <gtest/gtest.h>

#include "log_writers/console_writer.h"

#include <memory>

TEST(ConsoleWriter, WriteToOutput)
{
    std::unique_ptr<LogWriter> writer = std::make_unique<ConsoleWriter>();
    
    writer->write_log(LogLevel::Level::INFO, "Test");
}