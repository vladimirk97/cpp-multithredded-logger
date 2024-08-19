#ifndef LOG_WRITERS_CONSOLE_WRITER_H_
#define LOG_WRITERS_CONSOLE_WRITER_H_

#include "interfaces/log_writer.h"

namespace MTLogger
{
class ConsoleWriter: public LogWriter
{
  public:
    virtual bool write_log(LogLevel::Level severity_level, std::string record) override;
};  
} // namespace MTLogger

#endif // LOG_WRITERS_CONSOLE_WRITER_H_