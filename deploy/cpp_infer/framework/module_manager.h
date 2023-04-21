#ifndef MODULE_MANAGER_H
#define MODULE_MANAGER_H
#include <cstdint>
#include "status_code/status_code.h"
#include <memory>
#include "module_base.h"
#include "module_data_type.h"
#include <vector>
#include <string>
namespace MindOCR
{
    class ModuleManager
    {
    public:
        ModuleManager();
        ~ModuleManager();
        STATUS_CODE Init(BlockingQueue<void> &messageQueue, BlockingQueue<void> &taskQueue);
        STATUS_CODE DeInit(void);
        STATUS_CODE RegisterModules(const std::string pipelineName, std::vector<ModuleDesc> &moduleDesc, const int defaultCount);
        STATUS_CODE RegisterModulesConnects(const std::string pipelineName, std::vector<ModuleDesc> &moduleDesc);
        STATUS_CODE RegisterInputQueue(std::vector<std::shared_ptr<BlockingQueue<std::shared_ptr<void>>>> inputQueue);
        STATUS_CODE RunPipeline();
        STATUS_CODE DeInitPipelineModule();
        static void StopModule(std::shared_ptr<ModuleBase> moduleInstance);

    private:
        const std::string deviceId = 0;
        std::shared_ptr<void> pipelineMap;
    };

}

#endif