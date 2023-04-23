#ifndef CLS_INFER_PROCESS_H
#define CLS_INFER_PROCESS_H
#include "../../framework/ModuleBase.h"
#include "../../status_code//status_code.h"
#include "../../framework/ModuleInfer.h"
#include "../../data_type/process_data.h"
using MindOCR::ModelBase;
namespace MindOCR
{
    class CLSInferProcess : public MindOCR::ModuleBase
    {
    public:
        CLSInferProcess();
        ~CLSInferProcess();
        STATUS_CODE Init(std::shared_ptr<BlockingQueue<std::shared_ptr<void>>> msgQueue, ContextInfo &contextInfo);
        STATUS_CODE DeInit();

    protected:
        STATUS_CODE Process(std::shared_ptr<void> inputData);

    private:
        const float thresh = 0.9;
        std::unique_ptr<Model> model;
    };

} // namespace MindOCR
#endif