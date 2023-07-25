#pragma once

#include "include/mslite_inference.h"
#include <include/postprocess_op.h>
#include <include/preprocess_op.h>

namespace mindspore_infer {

    class DBDetector {
    public:
        explicit DBDetector(const std::string &model_path,
                            const int &cpu_num_threads,
                            const std::string &precision) {
          this->cpu_num_threads_ = cpu_num_threads;
          this->precision_ = precision;

          LoadModel(model_path);
        }

        // Load Paddle inference model
        void LoadModel(const std::string &model_path);

        // Run predictor
        void Run(cv::Mat &img, std::vector<std::vector<std::vector<int>>> &boxes,
                 std::vector<double> &times);

    private:
        std::shared_ptr<mslite_infer::Predictor> predictor_;

        int cpu_num_threads_ = 4;
        std::string precision_ = "fp32";

        // post-process params
        std::string limit_type_ = "max";
        int limit_side_len_ = 960;

        double det_db_thresh_ = 0.3;
        double det_db_box_thresh_ = 0.6;
        double det_db_unclip_ratio_ = 1.5;
        std::string det_db_score_mode_ = "slow";
        bool use_dilation_ = false;

        // pre-process params
        std::vector<float> mean_ = {0.485f, 0.456f, 0.406f};
        std::vector<float> scale_ = {1 / 0.229f, 1 / 0.224f, 1 / 0.225f};
        bool is_scale_ = true;

        // pre-process
        ResizeImgType0 resize_op_;
        Normalize normalize_op_;
        Permute permute_op_;

        // post-process
        DBPostProcessor post_processor_;
    };

} // namespace PaddleOCR
