#include <include/ocr_cls.h>

namespace mindspore_infer {

    void Classifier::Run(std::vector<cv::Mat> img_list,
                         std::vector<int> &cls_labels,
                         std::vector<float> &cls_scores,
                         std::vector<double> &times) {
      std::chrono::duration<float> preprocess_diff =
              std::chrono::steady_clock::now() - std::chrono::steady_clock::now();
      std::chrono::duration<float> inference_diff =
              std::chrono::steady_clock::now() - std::chrono::steady_clock::now();
      std::chrono::duration<float> postprocess_diff =
              std::chrono::steady_clock::now() - std::chrono::steady_clock::now();

      int img_num = img_list.size();
      std::vector<int> cls_image_shape = {3, 48, 192};
      for (int beg_img_no = 0; beg_img_no < img_num;
           beg_img_no += this->cls_batch_num_) {
        auto preprocess_start = std::chrono::steady_clock::now();
        int end_img_no = std::min(img_num, beg_img_no + this->cls_batch_num_);
        int batch_num = end_img_no - beg_img_no;
        // preprocess
        std::vector<cv::Mat> norm_img_batch;
        for (int ino = beg_img_no; ino < end_img_no; ino++) {
          cv::Mat srcimg;
          img_list[ino].copyTo(srcimg);
          cv::Mat resize_img;
          this->resize_op_.Run(srcimg, resize_img,
                               cls_image_shape);

          this->normalize_op_.Run(&resize_img, this->mean_, this->scale_,
                                  this->is_scale_);
          if (resize_img.cols < cls_image_shape[2]) {
            cv::copyMakeBorder(resize_img, resize_img, 0, 0, 0,
                               cls_image_shape[2] - resize_img.cols,
                               cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
          }
          norm_img_batch.push_back(resize_img);
        }
        std::vector<float> input(batch_num * cls_image_shape[0] *
                                 cls_image_shape[1] * cls_image_shape[2],
                                 0.0f);
        this->permute_op_.Run(norm_img_batch, input.data());
        auto preprocess_end = std::chrono::steady_clock::now();
        preprocess_diff += preprocess_end - preprocess_start;

        // inference.
        auto inference_start = std::chrono::steady_clock::now();

        std::vector<std::vector<float>> inputs{input};
        std::vector<std::vector<int64_t>> inputs_shape = {
                {batch_num, cls_image_shape[0], cls_image_shape[1], cls_image_shape[2]}};

        std::vector<std::vector<float>> outputs;
        std::vector<std::vector<int64_t>> outputs_shape;

        this->predictor_->Predict(inputs, inputs_shape, outputs, outputs_shape);

        std::vector<float> predict_batch = outputs[0];
        std::vector<int64_t> predict_shape = outputs_shape[0];

        auto inference_end = std::chrono::steady_clock::now();
        inference_diff += inference_end - inference_start;

        // postprocess
        auto postprocess_start = std::chrono::steady_clock::now();
        for (int64_t batch_idx = 0; batch_idx < predict_shape[0]; batch_idx++) {
          int label = int(
                  Utility::argmax(predict_batch.begin() + batch_idx * predict_shape[1],
                                  predict_batch.begin() + (batch_idx + 1) * predict_shape[1]));
          float score = float(*std::max_element(
                  predict_batch.begin() + batch_idx * predict_shape[1],
                  predict_batch.begin() + (batch_idx + 1) * predict_shape[1]));
          cls_labels[beg_img_no + batch_idx] = label;
          cls_scores[beg_img_no + batch_idx] = score;
        }
        auto postprocess_end = std::chrono::steady_clock::now();
        postprocess_diff += postprocess_end - postprocess_start;
      }
      times.push_back(double(preprocess_diff.count() * 1000));
      times.push_back(double(inference_diff.count() * 1000));
      times.push_back(double(postprocess_diff.count() * 1000));
    }

    void Classifier::LoadModel(const std::string &model_path) {
      mslite_infer::Config config;
      config.model_path = model_path;
      config.device = "cpu";
      config.thread_num = this->cpu_num_threads_;
      config.precision = this->precision_;

      this->predictor_ = mslite_infer::CreatePredictor(config);
    }
} // namespace mindspore_infer
