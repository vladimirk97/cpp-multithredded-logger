#include "log_writers/console_writer.h"
#include "utils/timestamp.h"

#include <iostream>

bool MTLogger::ConsoleWriter::write_log(LogLevel::Level severity_level, std::string record)
{
    std::cout << timestamp() << LogLevel::get_level(severity_level) << record << std::endl;
    return true;
}