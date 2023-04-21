#ifndef MODULE_INFER_H
#define MODULE_INFER_H
#include <string>
#include <cstdint>
#include "module_data_type.h"
#include "error_code/error_code.h"
#include "infer_engine/model_base.h"
namespace MindOCR
{
    class Model
    {
    public:
        APP_ERROR Init(const std::string &engineType, const std::string &modelPath, const std::string &deviceId);
        APP_ERROR Infer(std::shared_ptr<void> &inputData, std::vector<std::shared_ptr<void>> &output);
        std::shared_ptr<ShapeInfo> GetShapeInfo();

    private:
        void Warmup();

    private:
        std::shared_ptr<void> model;
        std::string engineType;
    };

} // namespace MindOC

#endif