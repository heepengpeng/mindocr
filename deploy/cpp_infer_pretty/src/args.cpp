#include <gflags/gflags.h>

// common args
DEFINE_int32(cpu_threads, 10, "Num of threads with CPU.");
DEFINE_string(precision, "fp32", "Precision be one of fp32 or fp16");
DEFINE_string(res_save_dir, "./inference_results", "Save inference results path.");
DEFINE_string(input_images_dir, "", "Dir of input image.");

// detection related
DEFINE_string(det_model_path, "", "Path of det inference model.");
DEFINE_string(vis_det_save_dir, "", "Path of showing the detection results.");

// classification related
DEFINE_string(cls_model_path, "", "Path of cls inference model.");
DEFINE_double(cls_thresh, 0.9, "Threshold of cls_thresh.");
DEFINE_int32(cls_batch_num, 1, "cls_batch_num.");

// recognition related
DEFINE_string(rec_model_path, "", "Path of rec inference model.");
DEFINE_int32(rec_batch_num, 6, "rec_batch_num.");
DEFINE_string(rec_char_dict_path, "", "Path of dictionary.");
DEFINE_int32(rec_img_h, 48, "rec image height");
DEFINE_int32(rec_img_w, 320, "rec image width");
