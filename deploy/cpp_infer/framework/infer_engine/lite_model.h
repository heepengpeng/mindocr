#ifndef LITE_MODEL_H
#define LITE_MODEL_H

#include <string>
#include "model_base.h"
#include "../../runtime/include/api/model.h"
#include "../../runtime/include/context.h"
#include "../../runtime/include/api/status.h"
#include "../../runtime/include//api/types.h"
#include "../../status_code/status_code.h"
#include "../../data_type/process_data.h"
using mindspore::MSTensor;
namespace MindOCR
{
    class LiteModel : public MindOCR::ModelBase<MSTensor>
    {
    public:
        STATUS_CODE Init(ContextInfo& contextInfo);
        STATUS_CODE Infer(std::shared_ptr<void> inputData, std::vector<MSTensor> &output);

    private:
        STATUS_CODE InitModel();
    };
}

#endif