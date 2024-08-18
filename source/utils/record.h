#ifndef UTILS_RECORD_H_
#define UTILS_RECORD_H_

#include "utils/log_level.h"

#include <string>

typedef struct _LogRecord
{
    LogLevel::Level severity_level;
    std::string record;
} LogRecord;

#endif // UTILS_RECORD_H_