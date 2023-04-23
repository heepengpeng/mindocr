#ifndef CLS_PRE_PROCESS_H
#define CLS_PRE_PROCESS_H
#include "../../framework/ModuleBase.h"
#include "../../status_code/status_code.h"
namespace MindOCR
{
    class CLSPreProcess : public MindOCR::ModuleBase
    {
    public:
        CLSPreProcess();
        ~CLSPreProcess();
        STATUS_CODE Init();
        STATUS_CODE DeInit();

    protected:
        STATUS_CODE Process(std::shared_ptr<void> inputData);
    };
} // namespace MindOCR

#endif