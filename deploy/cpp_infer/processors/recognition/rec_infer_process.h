#ifndef REC_INFER_PROCESS_H
#define REC_INFER_PROCESS_H
#include "../../framework/module_base.h"
#include "../../data_type/process_data.h"
#include "../../error_code/error_code.h"
#include "../../framework/module_infer.h"
namespace MindOCR
{
    class RecInferProcess : public MindOCR::ModuleBase
    {
    public:
        RecInferProcess();
        ~RecInferProcess();
        APP_ERROR Init(std::shared_ptr<BlockingQueue<std::shared_ptr<void>>> msgQueue, ContextInfo &contextInfo);
        APP_ERROR DeInit();

    protected:
        APP_ERROR Process(std::shared_ptr<void> inputData);

    private:
        std::unique_ptr<Model> model;
    };
} // namespace MindOCR
#endif