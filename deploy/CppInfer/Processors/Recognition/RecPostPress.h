#ifndef REC_POST_PRESS_H
#define REC_POST_PRESS_H
#include "../../framework/ModuleBase.h"
#include "../../status_code/status_code.h"
namespace MindOCR
{
    class RecPostProcess : public MindOCR::ModuleBase
    {
    public:
        RecPostProcess();
        ~RecPostProcess();
        STATUS_CODE Init();
        STATUS_CODE DeInit();

    protected:
        STATUS_CODE Process(std::shared_ptr<void> inputData);
    };
} // namespace MindOCR
#endif