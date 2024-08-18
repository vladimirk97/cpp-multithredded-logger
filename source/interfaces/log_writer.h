#ifndef INTERFACES_LOG_WRITER_H_
#define INTERFACES_LOG_WRITER_H_

#include "utils/log_level.h"

#include <string>

class LogWriter
{
  public:  
    virtual bool write_log(LogLevel::Level severity_level, std::string record) = 0;
};

#endif