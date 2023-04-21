#include <iostream>
#include <vector>

#include "pipeline/pipeline_args.h"
#include "pipeline/pipeline.h"
int main(int argc, char **argv)
{
    google::ParseCommandLineFlags(&argc, &argv, true);
    checkArgs();
    buildPipeline();
    return 0;
}
