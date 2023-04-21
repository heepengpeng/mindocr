#ifndef CLS_INFER_PROCESS_H
#define CLS_INFER_PROCESS_H
#include "../../framework/module_base.h"
#include "../../error_code/error_code.h"
#include "../../framework/module_infer.h"
#include "../../data_type/process_data.h"
using MindOCR::ModelBase;
namespace MindOCR
{
    template <typename T>
    class CLSInferProcess : public MindOCR::ModuleBase
    {
    public:
        CLSInferProcess();
        ~CLSInferProcess();
        APP_ERROR Init(std::shared_ptr<BlockingQueue<std::shared_ptr<void>>> msgQueue, ContextInfo &contextInfo);
        APP_ERROR DeInit();

    protected:
        APP_ERROR Process(std::shared_ptr<void> inputData);

    private:
        const float thresh = 0.9;
        std::unique_ptr<Model> model;
    };

} // namespace MindOCR
#endif