#ifndef MODEL_BASE_H
#define MODEL_BASE_H

#include <cstdint>
#include <string>
#include "StatusCode.h"
#include "CommonData.h"

namespace MindOCR {
    class ModelBase {
    public:
        virtual STATUS_CODE Init();


        virtual std::vector<int64_t> GetInputShape();

        virtual std::vector<std::vector<int>> GetGear();

        virtual std::string GetModelPath();
    };
}

#endif