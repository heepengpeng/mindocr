#ifndef LITE_MODEL_H
#define LITE_MODEL_H

#include <string>
#include "ModelBase.h"
#include "include/api/model.h"
#include "include/api/context.h"
#include "include/api/status.h"
#include "include/api/types.h"
#include "StatusCode.h"
#include "CommonData.h"
#include "SafeUtils.h"
#include "ModuleManager.h"
#include <regex>
#include "StringUtils.h"

using mindspore::MSTensor;
using mindspore::Model;
namespace MindOCR {
    class LiteModel : public ModelBase {
    public:
        explicit LiteModel(ContextInfo &contextInfo);

        ~LiteModel();

        STATUS_CODE Init() override;

        std::vector<MSTensor> Infer(uint8_t *srcData, uint32_t batchSize, int64_t height, int64_t width) override;

        std::vector<int64_t> GetInputShape() override;

        std::vector<std::vector<int>> GetGear() override;

        std::string GetModelPath();

    private:
        std::unique_ptr<Model> m_model;
        std::vector<int64_t> m_shape;
        ContextInfo &m_contextInfo;


    };
}

#endif