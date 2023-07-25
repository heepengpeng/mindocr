#pragma once

#include <gflags/gflags.h>

// common args
DECLARE_int32(cpu_threads);
DECLARE_string(precision);
DECLARE_string(res_save_dir);
DECLARE_string(input_images_dir);

// detection related
DECLARE_string(det_model_path);
DECLARE_string(vis_det_save_dir);

// classification related
DECLARE_string(cls_model_path);
DECLARE_double(cls_thresh);
DECLARE_int32(cls_batch_num);
// recognition related
DECLARE_string(rec_model_path);
DECLARE_int32(rec_batch_num);
DECLARE_string(rec_char_dict_path);
DECLARE_int32(rec_img_h);
DECLARE_int32(rec_img_w);
