#ifndef HEADCOUNT_PROCESS_H
#define HEADCOUNT_PROCESS_H
#include "../../framework/ModuleBase.h"
#include "../../status_code/status_code.h"
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