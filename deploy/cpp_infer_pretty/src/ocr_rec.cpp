#include <include/ocr_rec.h>

namespace mindspore_infer {

    void CRNNRecognizer::Run(std::vector<cv::Mat> img_list,
                             std::vector<std::string> &rec_texts,
                             std::vector<float> &rec_text_scores,
                             std::vector<double> &times) {
      std::chrono::duration<float> preprocess_diff =
              std::chrono::steady_clock::now() - std::chrono::steady_clock::now();
      std::chrono::duration<float> inference_diff =
              std::chrono::steady_clock::now() - std::chrono::steady_clock::now();
      std::chrono::duration<float> postprocess_diff =
              std::chrono::steady_clock::now() - std::chrono::steady_clock::now();

      int img_num = img_list.size();
      std::vector<float> width_list;
      for (int i = 0; i < img_num; i++) {
        width_list.push_back(float(img_list[i].cols) / img_list[i].rows);
      }
      std::vector<int> indices = Utility::argsort(width_list);

      for (int beg_img_no = 0; beg_img_no < img_num;
           beg_img_no += this->rec_batch_num_) {
        auto preprocess_start = std::chrono::steady_clock::now();
        int end_img_no = std::min(img_num, beg_img_no + this->rec_batch_num_);
        int batch_num = end_img_no - beg_img_no;
        int imgH = this->rec_image_shape_[1];
        int imgW = this->rec_image_shape_[2];
        float max_wh_ratio = imgW * 1.0 / imgH;
        for (int ino = beg_img_no; ino < end_img_no; ino++) {
          int h = img_list[indices[ino]].rows;
          int w = img_list[indices[ino]].cols;
          float wh_ratio = w * 1.0 / h;
          max_wh_ratio = std::max(max_wh_ratio, wh_ratio);
        }

        int batch_width = imgW;
        std::vector<cv::Mat> norm_img_batch;
        for (int ino = beg_img_no; ino < end_img_no; ino++) {
          cv::Mat srcimg;
          img_list[indices[ino]].copyTo(srcimg);
          cv::Mat resize_img;
          this->resize_op_.Run(srcimg, resize_img, max_wh_ratio,
                               this->rec_image_shape_);
          this->normalize_op_.Run(&resize_img, this->mean_, this->scale_,
                                  this->is_scale_);
          norm_img_batch.push_back(resize_img);
          batch_width = std::max(resize_img.cols, batch_width);
        }

        std::vector<float> input(batch_num * 3 * imgH * batch_width, 0.0f);
        this->permute_op_.Run(norm_img_batch, input.data());
        auto preprocess_end = std::chrono::steady_clock::now();
        preprocess_diff += preprocess_end - preprocess_start;

        // Inference.
        std::vector<std::vector<float>> inputs{input};
        std::vector<std::vector<int64_t>> inputs_shape = {{batch_num, 3, imgH, batch_width}};

        std::vector<std::vector<float>> outputs;
        std::vector<std::vector<int64_t>> outputs_shape;

        std::cout << "start rec Predict" << std::endl;
        this->predictor_->Predict(inputs, inputs_shape, outputs, outputs_shape);
        std::cout << "end rec Predict" << std::endl;

        std::vector<int64_t> predict_shape = outputs_shape[0];
        std::vector<float> predict_batch = outputs[0];

        // ctc decode
        auto postprocess_start = std::chrono::steady_clock::now();
        for (int m = 0; m < predict_shape[0]; m++) {
          std::string str_res;
          int argmax_idx;
          int last_index = 0;
          float score = 0.f;
          int count = 0;
          float max_value = 0.0f;

          for (int n = 0; n < predict_shape[1]; n++) {
            // get idx
            argmax_idx = int(Utility::argmax(
                    predict_batch.begin() + (m * predict_shape[1] + n) * predict_shape[2],
                    predict_batch.begin() + (m * predict_shape[1] + n + 1) * predict_shape[2]));
            // get score
            max_value = float(*std::max_element(
                    predict_batch.begin() + (m * predict_shape[1] + n) * predict_shape[2],
                    predict_batch.begin() + (m * predict_shape[1] + n + 1) * predict_shape[2]));

            if (argmax_idx > 0 && (!(n > 0 && argmax_idx == last_index))) {
              score += max_value;
              count += 1;
              str_res += label_list_[argmax_idx];
            }
            last_index = argmax_idx;
          }
          score /= count;
          if (std::isnan(score)) {
            continue;
          }
          rec_texts[indices[beg_img_no + m]] = str_res;
          rec_text_scores[indices[beg_img_no + m]] = score;
        }
        std::vector<float>().swap(predict_batch);
        std::vector<int64_t>().swap(predict_shape);
        auto postprocess_end = std::chrono::steady_clock::now();
        postprocess_diff += postprocess_end - postprocess_start;
      }
      times.push_back(double(preprocess_diff.count() * 1000));
      times.push_back(double(inference_diff.count() * 1000));
      times.push_back(double(postprocess_diff.count() * 1000));
    }

    void CRNNRecognizer::LoadModel(const std::string &model_path) {
      mslite_infer::Config config;
      config.model_path = model_path;
      config.device = "cpu";
      config.thread_num = this->cpu_num_threads_;
      config.precision = this->precision_;

      this->predictor_ = mslite_infer::CreatePredictor(config);
    }

} // namespace mindspore_infer
