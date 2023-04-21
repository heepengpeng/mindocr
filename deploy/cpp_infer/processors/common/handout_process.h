#ifndef HEADCOUNT_PROCESS_H
#define HEADCOUNT_PROCESS_H
#include "../../framework/module_base.h"
#include "../../error_code/error_code.h"
namespace MindOCR
{
    class HandoutProcess : public MindOCR::ModuleBase
    {
    public:
        HandoutProcess();
        ~HandoutProcess();
        APP_ERROR Init();
        APP_ERROR DeInit();

    protected:
        APP_ERROR Process(std::shared_ptr<void> inputData);

    private:
        uint32_t imageId = 0;
        uint32_t imageTotal = 0;
    };
} // namespace MindOCR
#endif