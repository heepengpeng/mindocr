#ifndef PIPELINE_H
#define PIPELINE_H
#include "../BlockingQueue/BlockingQueue.h"
#include <memory>
namespace MindOCR
{
    void ImageSender(const std::string &imagePath, std::shared_ptr<BlockingQueue<std::shared_ptr<void>>> sendQueue);
    void BuildPipelineKernel(std::shared_ptr<BlockingQueue<std::shared_ptr<void>>> inputQueue);
    void BuildPipeline(CommandParser &options);
};
#endif