#ifndef MODULE_MANAGER_H
#define MODULE_MANAGER_H
#include <cstdint>
#include "error_code/error_code.h"
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
        APP_ERROR Init(BlockingQueue<void> &messageQueue, BlockingQueue<void> &taskQueue);
        APP_ERROR DeInit(void);
        APP_ERROR RegisterModules(const std::string pipelineName, std::vector<ModuleDesc> &moduleDesc, const int defaultCount);
        APP_ERROR RegisterModulesConnects(const std::string pipelineName, std::vector<ModuleDesc> &moduleDesc);
        APP_ERROR RegisterInputQueue(std::vector<std::shared_ptr<BlockingQueue<std::shared_ptr<void>>>> inputQueue);
        APP_ERROR RunPipeline();
        APP_ERROR DeInitPipelineModule();
        static void StopModule(std::shared_ptr<ModuleBase> moduleInstance);

    private:
        const std::string deviceId = 0;
        std::shared_ptr<void> pipelineMap;
    };

}

#endif