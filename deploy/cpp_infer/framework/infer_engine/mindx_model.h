#ifndef MINDX_MODEL_H
#define MINDX_MODEL_H
#include <string>
#include "model_base.h"
#include "MxBase/MxBase.h"
using MxBase::Tensor;
namespace MindOCR
{
    class MindXModel : public MindOCR<MxBase::Tensor>::ModelBase
    {
    public:
        APP_ERROR Init(const std::stirng &modelPath, const std::string &deviceId);
        APP_ERROR Infer(std::shared_ptr<void> inputData, std::vector<Tensor> &output);

    private:
        APP_ERROR InitModel();
    };
}

#endif