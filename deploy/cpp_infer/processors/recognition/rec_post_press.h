#ifndef REC_POST_PRESS_H
#define REC_POST_PRESS_H
#include "../../framework/module_base.h"
#include "../../error_code/error_code.h"
namespace MindOCR
{
    class RecPostProcess : public MindOCR::ModuleBase
    {
    public:
        RecPostProcess();
        ~RecPostProcess();
        APP_ERROR Init();
        APP_ERROR DeInit();

    protected:
        APP_ERROR Process(std::shared_ptr<void> inputData);
    };
} // namespace MindOCR
#endif