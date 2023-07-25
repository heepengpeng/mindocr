#pragma once

#include "include/mslite_inference.h"

#include <include/preprocess_op.h>
#include <include/utility.h>

namespace mindspore_infer {

    class Classifier {
    public:
        explicit Classifier(const std::string &model_path,
                            const int &cpu_num_threads,
                            const double &cls_thresh,
                            const std::string &precision,
                            const int &cls_batch_num) {
          this->cpu_num_threads_ = cpu_num_threads;

          this->cls_thresh = cls_thresh;
          this->precision_ = precision;
          this->cls_batch_num_ = cls_batch_num;

          LoadModel(model_path);
        }

        double cls_thresh = 0.9;

        // Load Paddle inference model
        void LoadModel(const std::string &model_dir);

        void Run(std::vector<cv::Mat> img_list, std::vector<int> &cls_labels,
                 std::vector<float> &cls_scores, std::vector<double> &times);

    private:
        std::shared_ptr<mslite_infer::Predictor> predictor_;

        int cpu_num_threads_ = 4;

        std::vector<float> mean_ = {0.5f, 0.5f, 0.5f};
        std::vector<float> scale_ = {1 / 0.5f, 1 / 0.5f, 1 / 0.5f};
        bool is_scale_ = true;
        std::string precision_ = "fp32";
        int cls_batch_num_ = 1;
        // pre-process
        ClsResizeImg resize_op_;
        Normalize normalize_op_;
        PermuteBatch permute_op_;

    }; // class Classifier

} // namespace PaddleOCR
