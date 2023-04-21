#ifndef BUILD_H
#define BUILD_H

#include <vector>
#include <cstdint>
#include <string>
#include <unordered_map>
#include "opencv2/core.hpp"
#include "../../error_code/error_code.h"
namespace MindOCR
{
    class PreProcessor
    {
    public:
        APP_ERROR Init(const std::string &algorithm, std::unordered_map<std::string, std::string> &init_params);
        APP_ERROR Process(cv::Mat &img, cv::Mat &dst_img);

    private:
        const std::string algorithm;
        std::shared_ptr<std::vector<std::shared_ptr<void>>> opsList;
    };
}

#endif