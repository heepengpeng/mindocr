#ifndef REC_PRE_PROCESS_H
#define REC_PRE_PROCESS_H
#include "../../framework/ModuleBase.h"
#include "../../status_code/status_code.h"
namespace MindOCR
{
    class RecPreProcess : public MindOCR::ModuleBase
    {
    public:
        RecPreProcess();
        ~RecPreProcess();
        STATUS_CODE Init();
        STATUS_CODE DeInit();

    protected:
        STATUS_CODE Process(std::shared_ptr<void> inputData);
    };
} // namespace MindOCR

#endif