#ifndef PIPELINE_ARGS_H
#define PIPELINE_ARGS_H

#include "../StatusCode/StatusCode.h"
#include "../CommandParser/CommandParser.h"
#include <cstdint>
namespace MindOCR {
    STATUS_CODE ParseArgs(int argc, const char* argv[], CommandParser& options);
}

#endif