#ifndef MODEL_BASE_H
#define MODEL_BASE_H
#include <cstdint>
#include <string>
#include "opencv.hpp"
#include "error_code/error_code.h"
namespace MindOCR
{
    template <typename T>
    class ModelBase
    {
    public:
        virtual APP_ERROR Init(const std::string &modelPath, const std::string &deviceId);
        virtual APP_ERROR Infer(std::shared_ptr<void> inputData, std::vector<T> &output);

    private:
        virtual APP_ERROR InitModel()
    };
}

#endif