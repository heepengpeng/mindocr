#ifndef DB_POSTPROCESS_H
#define DB_POSTPROCESS_H
#include <cstdint>
#include <string>
#include <memory>
#include "../../status_code/status_code.h"
namespace MindOCR
{
    class DBPostProcess
    {
    public:
        DBPostProcess(){};
        ~DBPostProcess(){};
        STATUS_CODE Init();
        STATUS_CODE Run(std::shared_ptr<void> shrink_map, const uint32_t src_width, const uint32_t src_height);

    private:
        const uint32_t m_MaxCandidates = 1000;
        const uint32_t m_unclipDistance = 2;
        const uint32_t m_minSize = 3;
        const float m_binaryThresh = 0.5;
        const float m_boxThresh = 0.5;
        const float m_scoreThresh = 0.;
        const float m_unclipRatio = 2.;
        const std::string m_scoreMode = "fast";
    };
}
#endif
