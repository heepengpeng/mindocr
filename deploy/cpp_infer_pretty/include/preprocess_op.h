#pragma once

#include <iostream>
#include <vector>

#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"

namespace mindspore_infer {

    class Normalize {
    public:
        virtual void Run(cv::Mat *im, const std::vector<float> &mean,
                         const std::vector<float> &scale, const bool is_scale = true);
    };

// RGB -> CHW
    class Permute {
    public:
        virtual void Run(const cv::Mat *im, float *data);
    };

    class PermuteBatch {
    public:
        virtual void Run(const std::vector<cv::Mat> &imgs, float *data);
    };

    class ResizeImgType0 {
    public:
        virtual void Run(const cv::Mat &img, cv::Mat &resize_img,
                         std::string limit_type, int limit_side_len, float &ratio_h,
                         float &ratio_w);
    };

    class CrnnResizeImg {
    public:
        virtual void Run(const cv::Mat &img, cv::Mat &resize_img, float wh_ratio,
                         const std::vector<int> &rec_image_shape = {3, 32, 320});
    };

    class ClsResizeImg {
    public:
        virtual void Run(const cv::Mat &img, cv::Mat &resize_img,
                         const std::vector<int> &rec_image_shape = {3, 48, 192});
    };


    class Resize {
    public:
        virtual void Run(const cv::Mat &img, cv::Mat &resize_img, const int h,
                         const int w);
    };

} // namespace PaddleOCR
