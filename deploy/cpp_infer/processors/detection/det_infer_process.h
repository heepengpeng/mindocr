#ifndef DET_INFER_PROCESS_H
#define DET_INFER_PROCESS_H
#include "../../framework/module_base.h"
#include "../../error_code/error_code.h"
#include "../../framework/module_infer.h"
#include "../../data_type/process_data.h"
namespace MindOCR
{
    class DetInferProcess : public MindOCR::ModuleBase
    {
    public:
        DetInferProcess();
        ~DetInferProcess();
        APP_ERROR Init(std::shared_ptr<BlockingQueue<std::shared_ptr<void>>> msgQueue, ContextInfo &contextInfo);
        APP_ERROR DeInit();

    protected:
        APP_ERROR Process(std::shared_ptr<void> inputData);

    private:
        std::unique_ptr<Model> model;
    };
} // namespace MindOCR
#endif