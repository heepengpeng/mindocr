# 接口文档

## 1. infer接口
调用格式
```shell
./dist/infer --input_iamges_dir /dataset/ --engine mindx --device Ascend
```
### 1.1 输入参数
* input_images_dir， 输入图片路径
* engine，引擎（mindx, lite）
* device，设备类型（Ascend）
* device_id，设备id
* parallel_num，并行度
* precision_mode，fp16/fp32
* det_algorithm, 检查算法，默认DBNet
* rec_algorithm，识别算法，CRNN
* det_model_path，检查模型路径
* cls_model_path，分类模型路径
* rec_model_path，识别模型路径
* rec_char_dict_path，用于识别模型的字符字典文件路径
* res_save_dir，推理结果路径
* vis_det_save_dir，用于保存检测结果可视化的目录
* vis_pipeline_save_dir，用于保存检测+分类+识别结果可视化的目录
* vis_font_path，用于识别模型的字体文件路径
* pipeline_crop_save_dir，用于保存管道中裁剪的图像的目录
* show_log，是否显示日志
* save_log_dir，日志保存路径