#include <gtest/gtest.h>

#include "log_writers/console_writer.h"

#include <memory>

TEST(ConsoleWriter, WriteToOutput)
{
    std::unique_ptr<MTLogger::LogWriter> writer = std::make_unique<MTLogger::ConsoleWriter>();
    
    writer->write_log(MTLogger::LogLevel::Level::INFO, "Test");
}