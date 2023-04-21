#ifndef MODULE_BASE_H
#define MODULE_BASE_H
#include "error_code/error_code.h"
#include <cstdint>
#include <memory>
#include <atomic>
#include "blocking_queue.h"
#include <map>
namespace MindOCR
{

    class ModuleBase
    {
    public:
        ModuleBase(){};
        ~ModuleBase(){};
        virtual APP_ERROR Init();
        virtual APP_ERROR DeInit(void) = 0;
        void SetInputVec(std::shared_ptr<BlockingQueue<std::shared_ptr<void>>> inputQueue);
        void SetOutputVec(std::shared_ptr<BlockingQueue<std::shared_ptr<void>>> outputQueue);
        APP_ERROR Process(void);
        APP_ERROR Stop(void);

        void SendToNextModule(std::shared_ptr<void> outputData);
        const std::string GetModuleName();
        const int GetInstanceId();

    protected:
        std::string pipelineName = "";
        std::string moduleName = "";
        bool withoutInputQueue = false;
        int instanceId = 0;
        int32_t deviceId = -1;
        std::atomic_bool isStop = false;
        std::shared_ptr<BlockingQueue<std::shared_ptr<void>>> messageQueue = nullptr;
        std::shared_ptr<BlockingQueue<std::shared_ptr<void>>> inputQueue = nullptr;
        std::shared_ptr<BlockingQueue<std::shared_ptr<void>>> outputQueue = nullptr;
    };

}

#endif