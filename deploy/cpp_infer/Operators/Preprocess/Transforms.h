#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <iostream>
#include <vector>
#include "opencv2/core.hpp"
#include <tuple>
namespace MindOCR
{
    class NormalizeImage
    {
        virtual void Run(cv::Mat *im, const float scale, const std::vector<float> &std, const std::vector<float> &mean);
    };

    class ToNCHW
    {
        virtual void Run(cv::Mat &img, cv::Mat &dst_img);
    };

    class LimitMaxSide
    {
        virtual void Run(cv::Mat &img, cv::Mat &dst_img, const uint32_t limit_side);
    };

    class ResizeKeepAspectRatio
    {
        virtual void Run(cv::Mat &img, cv::Mat &dst_img, const std::tuple<uint32_t> &dst_hw);
    };

    class Resize
    {
        virtual void Run(cv::Mat &img, cv::Mat &dst_img, const std::tuple<uint32_t> &dst_hw);
    };
};

#endif