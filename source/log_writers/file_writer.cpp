#include "log_writers/file_writer.h"
#include "utils/timestamp.h"

MTLogger::FileWriter::FileWriter(std::string log_file_dir)
{
    std::string log_file = log_file_dir + "/" + timestamp();
    
    try
    {
        m_file.open(log_file, std::ofstream::app);
    }
    catch(const std::exception& e)
    {
        try
        {
            m_file.close();
        }
        catch(...){}
        throw(e);
    }
}


MTLogger::FileWriter::~FileWriter()
{
    m_file.close();
}

bool MTLogger::FileWriter::write_log(LogLevel::Level severity_level, std::string record)
{
    m_file << timestamp() << LogLevel::get_level(severity_level) << record << "\n";
    m_file.flush();
    return true; 
}