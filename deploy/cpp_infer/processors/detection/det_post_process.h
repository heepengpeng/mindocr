#ifndef DET_POST_PROCESS_H
#define DET_POST_PROCESS_H
#include "../../framework/module_base.h"
#include "../../error_code/error_code.h"
namespace MindOCR
{
    class DetPostProcess : public MindOCR::ModuleBase
    {
    public:
        DetPostProcess();
        ~DetPostProcess();
        APP_ERROR Init();
        APP_ERROR DeInit();

    protected:
        uint8_t Process(std::shared_ptr<void> inputData);
    };
} // namespace MindOCR
#endif