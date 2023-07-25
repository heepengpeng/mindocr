#pragma once

#include "include/mslite_inference.h"

#include <include/ocr_cls.h>
#include <include/utility.h>

namespace mindspore_infer {

    class CRNNRecognizer {
    public:
        explicit CRNNRecognizer(const std::string &model_path,
                                const int &cpu_num_threads,
                                const std::string &label_path,
                                const std::string &precision,
                                const int &rec_batch_num, const int &rec_img_h,
                                const int &rec_img_w) {
          this->cpu_num_threads_ = cpu_num_threads;
          this->precision_ = precision;
          this->rec_batch_num_ = rec_batch_num;
          this->rec_img_h_ = rec_img_h;
          this->rec_img_w_ = rec_img_w;
          std::vector<int> rec_image_shape = {3, rec_img_h, rec_img_w};
          this->rec_image_shape_ = rec_image_shape;

          this->label_list_ = Utility::ReadDict(label_path);
          this->label_list_.insert(this->label_list_.begin(),
                                   "#"); // blank char for ctc
          this->label_list_.emplace_back(" ");

          LoadModel(model_path);
        }

        // Load Paddle inference model
        void LoadModel(const std::string &model_path);

        void Run(std::vector<cv::Mat> img_list, std::vector<std::string> &rec_texts,
                 std::vector<float> &rec_text_scores, std::vector<double> &times);

    private:
        std::shared_ptr<mslite_infer::Predictor> predictor_;

        int cpu_num_threads_ = 4;

        std::vector<std::string> label_list_;

        std::vector<float> mean_ = {0.5f, 0.5f, 0.5f};
        std::vector<float> scale_ = {1 / 0.5f, 1 / 0.5f, 1 / 0.5f};
        bool is_scale_ = true;
        std::string precision_ = "fp32";
        int rec_batch_num_ = 6;
        int rec_img_h_ = 32;
        int rec_img_w_ = 320;
        std::vector<int> rec_image_shape_ = {3, rec_img_h_, rec_img_w_};
        // pre-process
        CrnnResizeImg resize_op_;
        Normalize normalize_op_;
        PermuteBatch permute_op_;

    }; // class CrnnRecognizer

} // namespace PaddleOCR
