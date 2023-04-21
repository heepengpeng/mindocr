#ifndef DET_POST_PROCESS_H
#define DET_POST_PROCESS_H
#include "../../framework/module_base.h"
#include "../../status_code/status_code.h"
namespace MindOCR
{
    class DetPostProcess : public MindOCR::ModuleBase
    {
    public:
        DetPostProcess();
        ~DetPostProcess();
        STATUS_CODE Init();
        STATUS_CODE DeInit();

    protected:
        uint8_t Process(std::shared_ptr<void> inputData);
    };
} // namespace MindOCR
#endif