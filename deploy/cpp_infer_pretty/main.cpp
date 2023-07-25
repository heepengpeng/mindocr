#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include <vector>

#include <include/args.h>
#include <include/mindocr.h>

using namespace mindspore_infer;

void check_params() {
  if (FLAGS_input_images_dir.empty()) {
    std::cout << "--input_images_dir is empty." << std::endl;
    exit(1);
  }

  if (!FLAGS_det_model_path.empty() && !Utility::PathExists(FLAGS_det_model_path)) {
    std::cerr << "--det_model_path=" << FLAGS_det_model_path << " doesn't exist." << std::endl;
    exit(1);
  }

  if (!FLAGS_rec_model_path.empty() && !Utility::PathExists(FLAGS_rec_model_path)) {
    std::cerr << "--rec_model_path=" << FLAGS_rec_model_path << " doesn't exist." << std::endl;
    exit(1);
  }

  if (!FLAGS_cls_model_path.empty() && !Utility::PathExists(FLAGS_cls_model_path)) {
    std::cerr << "--cls_model_path=" << FLAGS_cls_model_path << " doesn't exist." << std::endl;
    exit(1);
  }

  if (FLAGS_precision != "fp32" && FLAGS_precision != "fp16") {
    std::cerr << "--precison must be in ['fp32', 'fp16']" << std::endl;
    exit(1);
  }

  if (FLAGS_det_model_path.empty() && FLAGS_rec_model_path.empty() && FLAGS_cls_model_path.empty()) {
    std::cerr
        << "Please ensure that at least one of --det_model_path, --rec_model_path and --cls_model_path is not empty."
        << std::endl;
    exit(1);
  }
}

void ocr(std::vector<cv::String> &cv_all_img_names) {
  bool need_det = !FLAGS_det_model_path.empty();
  bool need_cls = !FLAGS_cls_model_path.empty();
  bool need_rec = !FLAGS_rec_model_path.empty();

  MindOCR ocr = MindOCR();
  size_t batch_num = 0;
  if (need_det) {
    batch_num = 1;
  } else if (need_cls) {
    batch_num = FLAGS_cls_batch_num;
  } else {
    batch_num = FLAGS_rec_batch_num;
  }

  size_t images_num = cv_all_img_names.size();

  std::cout << "need_det" << need_det << std::endl;
  std::cout << "need_cls" << need_cls << std::endl;
  std::cout << "need_rec" << need_rec << std::endl;

  for (size_t i = 0; i < images_num; i++) {
    std::vector<cv::Mat> img_list;
    std::vector<cv::String> img_names;
    std::cout << "Process img" << i << std::endl;
    if (i % batch_num == 0) {
      auto start_pos = cv_all_img_names.begin() + i;
      auto end_pos = cv_all_img_names.begin() + min(i + batch_num, images_num);

      for (auto iter = start_pos; iter < end_pos; iter++) {
        cv::Mat img = cv::imread(*iter, cv::IMREAD_COLOR);
        if (!img.data) {
          std::cerr << "[ERROR] image read failed! image path: " << *iter << std::endl;
          continue;
        }
        img_list.push_back(img);
        img_names.push_back(*iter);
      }

      std::vector<std::vector<OCRPredictResult>> ocr_results =
          ocr.ocr(img_list, need_det, need_rec, need_cls);

      for (size_t j = 0; j < img_names.size(); ++j) {
        std::cout << "predict img: " << img_names[j] << std::endl;

        std::string file_name = Utility::basename(img_names[j]);
        auto res_str = Utility::result_to_file(ocr_results[j], FLAGS_res_save_dir,
                                               file_name, need_det, need_cls, need_rec);

        Utility::print_result(ocr_results[j]);
//        if (!FLAGS_vis_det_save_dir.empty() && need_det) {
//          cv::Mat srcimg = img_list[j];
//          Utility::VisualizeBboxes(srcimg, ocr_results[j],
//                                   FLAGS_vis_det_save_dir + "/" + file_name);
//        }
      }
    }
  }
}

int main(int argc, char **argv) {
  // Parsing command-line
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  check_params();

  if (!Utility::PathExists(FLAGS_input_images_dir)) {
    std::cerr << "[ERROR] image path not exist! input_images_dir: " << FLAGS_input_images_dir
              << std::endl;
    exit(1);
  }

  std::vector<cv::String> cv_all_img_names;
  cv::glob(FLAGS_input_images_dir, cv_all_img_names);
  std::cout << "total images num: " << cv_all_img_names.size() << std::endl;

  if (!Utility::PathExists(FLAGS_res_save_dir)) {
    Utility::CreateDir(FLAGS_res_save_dir);
  }
  if (!Utility::PathExists(FLAGS_vis_det_save_dir)) {
    Utility::CreateDir(FLAGS_vis_det_save_dir);
  }

  ocr(cv_all_img_names);
}
