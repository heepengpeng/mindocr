#ifndef LITE_MODEL_H
#define LITE_MODEL_H

#include <string>
#include "model_base.h"
#include "../../runtime/include/api/model.h"
#include "../../runtime/include/context.h"
#include "../../runtime/include/api/status.h"
#include "../../runtime/include//api/types.h"
#include "error_code/error_code.h"
using mindspore::MSTensor;
namespace MindOCR
{
    class LiteModel : public MindOCR::ModelBase<MSTensor>
    {
    public:
        APP_ERROR Init(const std::string &modelPath, const std::string &deviceId);
        APP_ERROR Infer(std::shared_ptr<void> inputData, std::vector<MSTensor> &output);

    private:
        APP_ERROR InitModel();
    };
}

#endif