#ifndef MODULE_INFER_H
#define MODULE_INFER_H

#include <string>
#include <cstdint>
#include "StatusCode.h"
#include "ModuleBase.h"
#include "CommonData.h"
#include "InferEngine/LiteModel.h"
#include "InferEngine/MindxModel.h"

namespace MindOCR {

    class Model {
    public:
        STATUS_CODE Init(InferEngine engineType, ContextInfo &contextInfo);

        STATUS_CODE Infer(std::shared_ptr<void> &inputData, std::vector<std::shared_ptr<void>> &output);

        std::shared_ptr<ShapeInfo> GetShapeInfo();


    private:
        void Warmup();


    private:
        std::shared_ptr<ModelBase> m_Model;
        InferEngine m_inferEngine;
    };

} // namespace MindOC

#endif