#ifndef REC_PRE_PROCESS_H
#define REC_PRE_PROCESS_H
#include "../../framework/module_base.h"
#include "../../error_code/error_code.h"
namespace MindOCR
{
    class RecPreProcess : public MindOCR::ModuleBase
    {
    public:
        RecPreProcess();
        ~RecPreProcess();
        APP_ERROR Init();
        APP_ERROR DeInit();

    protected:
        APP_ERROR Process(std::shared_ptr<void> inputData);
    };
} // namespace MindOCR

#endif