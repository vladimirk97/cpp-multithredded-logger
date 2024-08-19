#ifndef LOG_WRITERS_FILE_WRITER_H_
#define LOG_WRITERS_FILE_WRITER_H_

#include "interfaces/log_writer.h"

#include <fstream>

namespace MTLogger
{
class FileWriter: public LogWriter
{
  public:
    virtual bool write_log(LogLevel::Level severity_level, std::string record) override;
    
    FileWriter(std::string log_file_dir);
    ~FileWriter();

  private:
    std::ofstream m_file;

};
}

#endif // LOG_WRITERS_CONSOLE_WRITER_H_