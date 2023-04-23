#include <iostream>
#include <vector>
#include "CommandParser/CommandParser.h"
#include "Pipeline/PipelineArgs.h"
#include "Pipeline/Pipeline.h"
#include "StatusCode/StatusCode.h"
using namespace MindOCR;
int main(int argc, const char *argv[])
{

    CommandParser options;
    STATUS_CODE ret = ParseArgs(argc, argv, options);
    if (ret != STATUS_SUCCESS) {
        std::cerr << "Parser parameter failed.";
        exit(-1);
    }
    BuildPipeline(options);
    return 0;
}
