# 接口文档

调用格式
```shell
./dist/infer --input_iamges_dir /dataset/ --engine mindx --device Ascend
```
## 1. 检测+分类+识别串联

### 输入参数
| 参数名称  | 参数含义                   | 是否必须 | 默认值               |
|-------|------------------------|------|-------------------|
| input_images_dir | 输入图片路径                 | 是    | 无                 |
| det_model_path | 检测模型路径                 | 是    | 无                 |
| cls_model_path | 分类模型路径                 | 是    | 无                 |
| rec_model_path | 识别模型路径                 | 是    | 无                 |
| rec_char_dict_path | 文字识别字典路径               | 是    | 无                 |
| det_algorithm | 检测算法                   | 否    | DBNet             |
| rec_algorithm | 识别算法                   | 否    | CRNN              |
| vis_pipeline_save_dir | 检测+识别系统推理中，是否保存检测后裁剪图片 | 否    | 无                 |
| vis_font_path | 可视化文字文件路径              | 否    | 无                 |
| pipeline_crop_save_dir | 检测+识别系统推理中，是否保存检测后裁剪图片 | 否    | 无                 |
| engine | 推理引擎（mindx或lite）       | 否    | mindx             |
| device | 设备（Ascend）             | 否    | Ascend            |
| device_id | 设备id                   | 否    | 0                 |
| parallel_num | 并行度                    | 否    | 1                 |
| precision_mode | 精度类型（fp16/fp32）        | 否    | fp32              |
| res_save_dir | 推理结果路径                 | 否    | inference_results |
| show_log | 是否显示日志                 | 否    | False             |
| save_log_dir | 日志保存路径                 | 否    | 无                 |

### 输出格式
1. system_results.txt
* 多张图片时：{image_name}_{image_index}\t{res}, res为 [{\"transcription\":识别文本, \"points\":[bboxes]}]
* 单张图片时：{image_name}\t{res}, res为 [{\"transcription\":识别文本, \"points\":[bboxes]}]
2. 检测完成后裁剪出来的图片块
3. 画有文本检测框和文字的图片

## 2. 检测 + 识别
### 输入参数
| 参数名称  | 参数含义                   | 是否必须  | 默认值 |
|-------|------------------------|-------|-----|
| input_images_dir | 输入图片路径                 | 是     | 无   |
| det_model_path | 检测模型路径                 | 是     | 无   |
| rec_model_path | 识别模型路径                 | 是 | 无   |
| rec_char_dict_path | 文字识别字典路径               | 是 | 无   |
| det_algorithm | 检测算法                   | 否    | DBNet             |
| rec_algorithm | 识别算法                   | 否    | CRNN              |
| vis_pipeline_save_dir | 检测+识别系统推理中，是否保存检测后裁剪图片 | 否    | 无                 |
| vis_font_path | 可视化文字文件路径              | 否    | 无                 |
| pipeline_crop_save_dir | 检测+识别系统推理中，是否保存检测后裁剪图片 | 否    | 无                 |
| engine | 推理引擎（mindx或lite）       | 否    | mindx             |
| device | 设备（Ascend）             | 否    | Ascend            |
| device_id | 设备id                   | 否    | 0                 |
| parallel_num | 并行度                    | 否    | 1                 |
| precision_mode | 精度类型（fp16/fp32）        | 否    | fp32              |
| res_save_dir | 推理结果路径                 | 否    | inference_results |
| show_log | 是否显示日志                 | 否    | False             |
| save_log_dir | 日志保存路径                 | 否    | 无                 |

### 输出格式
1. system_results.txt
* 多张图片时：{image_name}_{image_index}\t{res}, res为 [{\"transcription\":识别文本, \"points\":[bboxes]}]
* 单张图片时：{image_name}\t{res}, res为 [{\"transcription\":识别文本, \"points\":[bboxes]}]
2. 检测完成后裁剪出来的图片块
3. 画有文本检测框和文字的图片

## 3. 检测
### 输入参数

| 参数名称  | 参数含义              | 是否必须  | 默认值 |
|-------|-------------------|-------|-----|
| input_images_dir | 输入图片路径            | 是     | 无   |
| det_model_path | 检测模型路径            | 是     | 无   |
| det_algorithm | 检测算法              | 否    | DBNet             |
| vis_det_save_dir | 可视化检测任务推理图像的保存文件夹 | 否    | DBNet             |
| vis_font_path | 可视化文字文件路径         | 否    | 无                 |
| engine | 推理引擎（mindx或lite）  | 否    | mindx             |
| device | 设备（Ascend）        | 否    | Ascend            |
| device_id | 设备id              | 否    | 0                 |
| parallel_num | 并行度               | 否    | 1                 |
| precision_mode | 精度类型（fp16/fp32）   | 否    | fp32              |
| res_save_dir | 推理结果路径            | 否    | inference_results |
| show_log | 是否显示日志            | 否    | False             |
| save_log_dir | 日志保存路径            | 否    | 无                 |

### 输出格式
1. det_results.txt
* 多张图片时：{image_name}_{image_index}\t{list of bboxes}
* 单张图片时：{image_name}\t{list of bboxes}
3. 画有文本检测框和文字的图片


## 4. 识别
### 输入参数
| 参数名称  | 参数含义   | 是否必须  | 默认值 |
|-------|--------|-------|-----|
| input_images_dir | 输入图片路径 | 是     | 无   |
| rec_model_path | 识别模型路径 | 是 | 无   |
| rec_char_dict_path | 文字识别字典路径 | 是 | 无   |
| engine | 推理引擎（mindx或lite）  | 否    | mindx             |
| device | 设备（Ascend）        | 否    | Ascend            |
| device_id | 设备id              | 否    | 0                 |
| parallel_num | 并行度               | 否    | 1                 |
| precision_mode | 精度类型（fp16/fp32）   | 否    | fp32              |
| res_save_dir | 推理结果路径            | 否    | inference_results |
| show_log | 是否显示日志            | 否    | False             |
| save_log_dir | 日志保存路径            | 否    | 无                 |

### 输出格式
rec_results.txt
Predicts of {image路径}:({识别文本}，预测分数)

示例： 

Predicts of ./doc/imgs_words/en/word_1.png:(\'JOINT\',0.998160719871521)

