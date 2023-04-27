#ifndef MINDX_MODEL_H
#define MINDX_MODEL_H

#include <string>
#include "ModelBase.h"
#include "CommonData.h"
#include "StatusCode.h"

using mindspore::MSTensor;
namespace MindOCR {
    class MindXModel : public ModelBase {
    public:
        explicit MindXModel(ContextInfo &contextInfo);

        STATUS_CODE Init(ContextInfo &contextInfo);

        std::vector<int64_t> Infer(void *inputData, std::vector<MSTensor> &output);

        std::vector<int64_t> GetInputShape() override;

        std::vector<std::vector<int>> GetGear() override;

        std::string GetModelPath() override;

    private:
        STATUS_CODE InitModel();
    };
}

#endif