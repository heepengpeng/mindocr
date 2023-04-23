#ifndef COLLECT_PROCESS_H
#define COLLECT_PROCESS_H
#include "../../framework/ModuleBase.h"
#include "../../status_code/status_code.h"
#include <map>
#include <vector>
namespace MindOCR
{
    class CollectProcess : public MindOCR::ModuleBase
    {
    public:
        CollectProcess();
        ~CollectProcess();
        STATUS_CODE Init(const std::string &taskType, const std::string &resSaveDir, std::shared_ptr<BlockingQueue<std::shared_ptr<void>>> msgQueue);
        STATUS_CODE DeInit();
        STATUS_CODE Stop();

    protected:
        STATUS_CODE Process(std::shared_ptr<void> inputData);

    private:
        std::map<uint32_t, uint32_t> imageSubRemaining;
        std::map<std::string, std::vector<std::shared_ptr<void>>> imagePipelineRes;
        uint32_t inferSize = 0;
        uint64_t imageTotal = 0;
        std::string taskType;
        std::string saveFileName;
        std::string resSaveDir;
    };
} // namespace MindOCR
#endif