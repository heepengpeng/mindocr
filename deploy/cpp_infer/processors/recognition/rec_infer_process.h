#ifndef REC_INFER_PROCESS_H
#define REC_INFER_PROCESS_H
#include "../../framework/module_base.h"
#include "../../data_type/process_data.h"
#include "../../status_code/status_code.h"
#include "../../framework/module_infer.h"
namespace MindOCR
{
    class RecInferProcess : public MindOCR::ModuleBase
    {
    public:
        RecInferProcess();
        ~RecInferProcess();
        STATUS_CODE Init(std::shared_ptr<BlockingQueue<std::shared_ptr<void>>> msgQueue, ContextInfo &contextInfo);
        STATUS_CODE DeInit();

    protected:
        STATUS_CODE Process(std::shared_ptr<void> inputData);

    private:
        std::unique_ptr<Model> model;
    };
} // namespace MindOCR
#endif