#ifndef PIPELINE_H
#define PIPELINE_H
#include "args.h"

namespace MindOCR
{
    void imageSender(const string &imagePath, std::shared_ptr<BlockingQueue<std::shared_ptr<void>>> sendQueue);
    void buildPipelineKernel(std::shared_ptr<BlockingQueue<std::shared_ptr<void>>> inputQueue);
    void buildPipeline();
};
#endif