#ifndef DB_POSTPROCESS_H
#define DB_POSTPROCESS_H
#include <cstdint>
#include <string>
#include <memory>
#include "../../error_code/error_code.h"
namespace MindOCR
{
    class DBPostProcess
    {
    public:
        DBPostProcess(){};
        ~DBPostProcess(){};
        APP_ERROR Init();
        APP_ERROR Run(std::shared_ptr<void> shrink_map, const uint32_t src_width, const uint32_t src_height);

    private:
        const uint32_t maxCandidates = 1000;
        const uint32_t unclipDistance = 2;
        const uint32_t minSize = 3;
        const float binaryThresh = 0.5;
        const float boxThresh = 0.5;
        const float scoreThresh = 0.;
        const float unclipRatio = 2.;
        const std::string scoreMode = "fast";
    };
}
#endif
