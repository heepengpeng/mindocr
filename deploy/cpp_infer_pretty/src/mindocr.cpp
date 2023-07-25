#include <include/args.h>
#include <include/mindocr.h>

namespace mindspore_infer {

    MindOCR::MindOCR() {
      if (!FLAGS_det_model_path.empty()) {
        this->detector_ = new DBDetector(
                FLAGS_det_model_path, FLAGS_cpu_threads, FLAGS_precision);
      }

      if (!FLAGS_cls_model_path.empty()) {
        this->classifier_ = new Classifier(
                FLAGS_cls_model_path,
                FLAGS_cpu_threads, FLAGS_cls_thresh,
                FLAGS_precision, FLAGS_cls_batch_num);
      }
      if (!FLAGS_rec_model_path.empty()) {
        this->recognizer_ = new CRNNRecognizer(
                FLAGS_rec_model_path,
                FLAGS_cpu_threads, FLAGS_rec_char_dict_path,
                FLAGS_precision, FLAGS_rec_batch_num,
                FLAGS_rec_img_h, FLAGS_rec_img_w);
      }
    };

    std::vector<std::vector<OCRPredictResult>>
    MindOCR::ocr(std::vector<cv::Mat> img_list, bool det, bool rec, bool cls) {
      std::vector<std::vector<OCRPredictResult>> ocr_results;

      if (!det) {
        std::vector<OCRPredictResult> ocr_result;
        ocr_result.resize(img_list.size());
        if (cls && this->classifier_ != nullptr) {
          this->cls(img_list, ocr_result);
          for (size_t i = 0; i < img_list.size(); i++) {
            if (ocr_result[i].cls_label % 2 == 1 &&
                ocr_result[i].cls_score > this->classifier_->cls_thresh) {
              cv::rotate(img_list[i], img_list[i], 1);
            }
          }
        }
        if (rec) {
          this->rec(img_list, ocr_result);
        }
        for (const auto &img_res: ocr_result) {
          std::vector<OCRPredictResult> ocr_result_tmp;
          ocr_result_tmp.push_back(img_res);
          ocr_results.push_back(ocr_result_tmp);
        }
      } else {
        for (const auto &img_res: img_list) {
          std::vector<OCRPredictResult> ocr_result =
                  this->ocr(img_res, true, rec, cls);
          ocr_results.push_back(ocr_result);
        }
      }
      return ocr_results;
    }

    std::vector<OCRPredictResult> MindOCR::ocr(cv::Mat img, bool det, bool rec,
                                               bool cls) {

      std::vector<OCRPredictResult> ocr_result;
      // det
      this->det(img, ocr_result);
      std::cout << "det finished" << std::endl;
      // crop image
      std::vector<cv::Mat> img_list;
      for (auto &res_j: ocr_result) {
        cv::Mat crop_img;
        crop_img = Utility::GetRotateCropImage(img, res_j.box);
        img_list.push_back(crop_img);
      }
      // cls
      if (cls && this->classifier_ != nullptr) {
        this->cls(img_list, ocr_result);
        for (size_t i = 0; i < img_list.size(); i++) {
          if (ocr_result[i].cls_label % 2 == 1 &&
              ocr_result[i].cls_score > this->classifier_->cls_thresh) {
            cv::rotate(img_list[i], img_list[i], 1);
          }
        }
      }
      // rec
      if (rec) {
        std::cout << "start rec" << std::endl;
        this->rec(img_list, ocr_result);
      }
      return ocr_result;
    }

    void MindOCR::det(cv::Mat img, std::vector<OCRPredictResult> &ocr_results) {
      std::vector<std::vector<std::vector<int>>> boxes;
      std::vector<double> det_times;

      this->detector_->Run(img, boxes, det_times);

      for (const auto &box: boxes) {
        OCRPredictResult res;
        res.box = box;
        ocr_results.push_back(res);
      }
      // sort boex from top to bottom, from left to right
      Utility::sorted_boxes(ocr_results);
      this->time_info_det[0] += det_times[0];
      this->time_info_det[1] += det_times[1];
      this->time_info_det[2] += det_times[2];
    }

    void MindOCR::rec(std::vector<cv::Mat> img_list,
                      std::vector<OCRPredictResult> &ocr_results) {
      std::vector<std::string> rec_texts(img_list.size(), "");
      std::vector<float> rec_text_scores(img_list.size(), 0);
      std::vector<double> rec_times;
      std::cout << "start rec run" << std::endl;
      this->recognizer_->Run(img_list, rec_texts, rec_text_scores, rec_times);
      std::cout << "end rec run" << std::endl;
      // output rec results
      for (size_t i = 0; i < rec_texts.size(); i++) {
        ocr_results[i].text = rec_texts[i];
        ocr_results[i].score = rec_text_scores[i];
      }
      this->time_info_rec[0] += rec_times[0];
      this->time_info_rec[1] += rec_times[1];
      this->time_info_rec[2] += rec_times[2];
    }

    void MindOCR::cls(std::vector<cv::Mat> img_list,
                      std::vector<OCRPredictResult> &ocr_results) {
      std::vector<int> cls_labels(img_list.size(), 0);
      std::vector<float> cls_scores(img_list.size(), 0);
      std::vector<double> cls_times;
      this->classifier_->Run(img_list, cls_labels, cls_scores, cls_times);
      // output cls results
      for (size_t i = 0; i < cls_labels.size(); i++) {
        ocr_results[i].cls_label = cls_labels[i];
        ocr_results[i].cls_score = cls_scores[i];
      }
      this->time_info_cls[0] += cls_times[0];
      this->time_info_cls[1] += cls_times[1];
      this->time_info_cls[2] += cls_times[2];
    }

    void MindOCR::reset_timer() {
      this->time_info_det = {0, 0, 0};
      this->time_info_rec = {0, 0, 0};
      this->time_info_cls = {0, 0, 0};
    }

    MindOCR::~MindOCR() {
      if (this->detector_ != nullptr) {
        delete this->detector_;
      }
      if (this->classifier_ != nullptr) {
        delete this->classifier_;
      }
      if (this->recognizer_ != nullptr) {
        delete this->recognizer_;
      }
    };

} // namespace mindspore_infer
