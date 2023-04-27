#ifndef HEADCOUNT_PROCESS_H
#define HEADCOUNT_PROCESS_H
#include "../../Framework/ModuleBase.h"
#include "../../StatusCode/StatusCode.h"
namespace MindOCR
{
    class HandoutProcess : public MindOCR::ModuleBase
    {
    public:
        HandoutProcess();
        ~HandoutProcess();
        STATUS_CODE Init();
        STATUS_CODE DeInit();

    protected:
        STATUS_CODE Process(std::shared_ptr<void> inputData);

    private:
        uint32_t imageId = 0;
        uint32_t imageTotal = 0;
    };
} // namespace MindOCR
#endif