#ifndef MODULE_BASE_H
#define MODULE_BASE_H
#include "../status_code/status_code.h"
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
        virtual STATUS_CODE Init();
        virtual STATUS_CODE DeInit(void) = 0;
        void SetInputVec(std::shared_ptr<BlockingQueue<std::shared_ptr<void>>> inputQueue);
        void SetOutputVec(std::shared_ptr<BlockingQueue<std::shared_ptr<void>>> outputQueue);
        STATUS_CODE Process(void);
        STATUS_CODE Stop(void);

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