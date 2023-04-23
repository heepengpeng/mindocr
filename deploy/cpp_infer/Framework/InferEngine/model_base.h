#ifndef MODEL_BASE_H
#define MODEL_BASE_H
#include <cstdint>
#include <string>
#include "opencv.hpp"
#include "../../status_code/status_code.h"
#include "../../data_type/process_data.h"
namespace MindOCR
{
    template <typename T>
    class ModelBase
    {
    public:
        virtual STATUS_CODE Init(ContextInfo& contextInfo);
        virtual STATUS_CODE Infer(std::shared_ptr<void> inputData, std::vector<T> &output);

    private:
        virtual STATUS_CODE InitModel()
    };
}

#endif