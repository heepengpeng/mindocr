#include <include/ocr_det.h>

namespace mindspore_infer {

    void DBDetector::LoadModel(const std::string &model_path) {
      mslite_infer::Config config;
      config.model_path = model_path;
      config.device = "cpu";
      config.thread_num = this->cpu_num_threads_;
      config.precision = this->precision_;

      this->predictor_ = mslite_infer::CreatePredictor(config);
    }

    void DBDetector::Run(cv::Mat &img,
                         std::vector<std::vector<std::vector<int>>> &boxes,
                         std::vector<double> &times) {
      float ratio_h{};
      float ratio_w{};

      cv::Mat srcimg;
      cv::Mat resize_img;
      img.copyTo(srcimg);

      auto preprocess_start = std::chrono::steady_clock::now();
      this->resize_op_.Run(img, resize_img, this->limit_type_,
                           this->limit_side_len_, ratio_h, ratio_w);

      this->normalize_op_.Run(&resize_img, this->mean_, this->scale_,
                              this->is_scale_);

      std::vector<float> input(1 * 3 * resize_img.rows * resize_img.cols, 0.0f);
      this->permute_op_.Run(&resize_img, input.data());
      auto preprocess_end = std::chrono::steady_clock::now();

      // Inference.
      auto inference_start = std::chrono::steady_clock::now();

      std::vector<std::vector<float>> inputs{input};
      std::vector<std::vector<int64_t>> inputs_shape = {{1, 3, resize_img.rows, resize_img.cols}};

      std::vector<std::vector<float>> outputs;
      std::vector<std::vector<int64_t>> outputs_shape;

      this->predictor_->Predict(inputs, inputs_shape, outputs, outputs_shape);

      auto inference_end = std::chrono::steady_clock::now();

      auto postprocess_start = std::chrono::steady_clock::now();

      auto output_shape = outputs_shape[0];
      auto output_data = outputs[0].data();

      int n2 = static_cast<int>(output_shape[2]);
      int n3 = static_cast<int>(output_shape[3]);
      int n = n2 * n3;

      std::vector<float> pred(n, 0.0);
      std::vector<unsigned char> cbuf(n, ' ');

      for (int i = 0; i < n; i++) {
        pred[i] = float(output_data[i]);
        cbuf[i] = (unsigned char) ((output_data[i]) * 255);
      }

      cv::Mat cbuf_map(n2, n3, CV_8UC1, (unsigned char *) cbuf.data());
      cv::Mat pred_map(n2, n3, CV_32F, (float *) pred.data());

      const double threshold = this->det_db_thresh_ * 255;
      const double maxvalue = 255;
      cv::Mat bit_map;
      cv::threshold(cbuf_map, bit_map, threshold, maxvalue, cv::THRESH_BINARY);
      if (this->use_dilation_) {
        cv::Mat dila_ele =
                cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2));
        cv::dilate(bit_map, bit_map, dila_ele);
      }

      boxes = post_processor_.BoxesFromBitmap(
              pred_map, bit_map, this->det_db_box_thresh_, this->det_db_unclip_ratio_,
              this->det_db_score_mode_);

      boxes = post_processor_.FilterTagDetRes(boxes, ratio_h, ratio_w, srcimg);
      auto postprocess_end = std::chrono::steady_clock::now();

      std::chrono::duration<float> preprocess_diff =
              preprocess_end - preprocess_start;
      times.push_back(double(preprocess_diff.count() * 1000));
      std::chrono::duration<float> inference_diff = inference_end - inference_start;
      times.push_back(double(inference_diff.count() * 1000));
      std::chrono::duration<float> postprocess_diff =
              postprocess_end - postprocess_start;
      times.push_back(double(postprocess_diff.count() * 1000));
    }

} // namespace mindspore_infer
