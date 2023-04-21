#ifndef CLS_PRE_PROCESS_H
#define CLS_PRE_PROCESS_H
#include "../../framework/module_base.h"
#include "../../error_code/error_code.h"
namespace MindOCR
{
    class CLSPreProcess : public MindOCR::ModuleBase
    {
    public:
        CLSPreProcess();
        ~CLSPreProcess();
        APP_ERROR Init();
        APP_ERROR DeInit();

    protected:
        APP_ERROR Process(std::shared_ptr<void> inputData);
    };
} // namespace MindOCR

#endif