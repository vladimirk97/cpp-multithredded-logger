#ifndef LOG_WRITERS_CONSOLE_WRITER_H_
#define LOG_WRITERS_CONSOLE_WRITER_H_

#include "interfaces/log_writer.h"

class ConsoleWriter: public LogWriter
{
  public:
    virtual bool write_log(LogLevel::Level severity_level, std::string record) override;
};

#endif // LOG_WRITERS_CONSOLE_WRITER_H_