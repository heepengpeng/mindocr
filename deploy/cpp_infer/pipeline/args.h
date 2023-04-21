#ifndef ARGS_H
#define ARGS_H
#include <gflags/gflags.h>
#include <cstdint>
DECLARE_string(input_imgaes_dir);
DECLARE_string(engine);
DECLARE_string(device);
DECLARE_int32(device_id);
DECLARE_int32(parallel_num);
DECLARE_string(precision_mode);
DECLARE_string(det_algorithm);
DECLARE_string(rec_algorithm);
DECLARE_string(det_model_path);
DECLARE_string(cls_model_path);
DECLARE_string(rec_model_path);
DECLARE_string(rec_char_dict_path);
DECLARE_string(res_save_dir);
DECLARE_string(vis_det_save_dir);
DECLARE_string(vis_pipeline_save_dir);
DECLARE_string(vis_font_path);
DECLARE_string(pipeline_crop_save_dir);
DECLARE_bool(show_log);
DECLARE_string(save_log_dir);
#endif