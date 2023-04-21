#ifndef MODULE_INFER_H
#define MODULE_INFER_H
#include <string>
#include <cstdint>
#include "module_data_type.h"
#include "../status_code/status_code.h"
#include "infer_engine/model_base.h"
#include "module_data_type.h"
namespace MindOCR
{
    class Model
    {
    public:
        STATUS_CODE Init(InferEngine engineType, ContextInfo &contextInfo);
        STATUS_CODE Infer(std::shared_ptr<void> &inputData, std::vector<std::shared_ptr<void>> &output);
        std::shared_ptr<ShapeInfo> GetShapeInfo();

    private:
        void Warmup();

    private:
        std::shared_ptr<void> model;
        InferEngine engineType;
    };

} // namespace MindOC

#endif