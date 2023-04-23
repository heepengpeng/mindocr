#ifndef MINDX_MODEL_H
#define MINDX_MODEL_H
#include <string>
#include "model_base.h"
#include "MxBase/MxBase.h"
#include "../../data_type/process_data.h"
#include "../../status_code/status_code.h"
using MxBase::Tensor;
namespace MindOCR
{
    class MindXModel : public MindOCR<MxBase::Tensor>::ModelBase
    {
    public:
        STATUS_CODE Init(ContextInfo &contextInfo);
        STATUS_CODE Infer(std::shared_ptr<void> inputData, std::vector<Tensor> &output);

    private:
        STATUS_CODE InitModel();
    };
}

#endif