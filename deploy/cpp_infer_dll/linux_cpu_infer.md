# Linux环境下MindOCR C++ 推理教程（使用CPU）

## 1. 依赖安装

### 1.1 mindspore-lite安装
打开 [MindSpore Lite 官方页面](https://www.mindspore.cn/lite/docs/zh-CN/r2.0/use/downloads.html), 请用户根据使用的操作系统下载对应包，这里以Linux-x86-64为例，
下载 [MindSpore Lite 安装包](https://ms-release.obs.cn-north-4.myhuaweicloud.com/2.0.0/MindSpore/lite/release/linux/x86_64/cloud_fusion/python37/mindspore-lite-2.0.0-linux-x64.tar.gz)。下载完成后放到用户自定义目录。
然后执行下面的命令进行解压。

```shell
tar xvf mindspore-lite-2.0.0-linux-x64.tar.gz
```
为了保证 MindOCR C++推理代码编译成功，需要设置 ```LITE_HOME``` 环境变量为解压缩 MindSpore Lite 安装包的路径。

```shell
export LITE_HOME=$some_path/mindspore-lite-2.0.0-linux-x64
```

由于MindOCR C++ 推理代码用到了OpenCV库，这里我们使用 MindSpore Lite 自带的OpenCV库，以免额外安装的OpenCV库与MindSpore Lite 自带的OpenCV库产生冲突。
切换到 ```$LITE_HOME/tools/converter/lib``` 下，
设置软链接：
```shell
ln -s libopencv_core.s0.4.5 libopencv_core.s0
ln -s libopencv_imgcodesc.s0.4.5 libopencv_imgcodesc.s0
ln -s libopencv_imgproc.s0.4.5 libopencv_imgproc.s0
```

设置环境变量 ```LD_LIBRARY_PATH```

```shell
export LD_LIBRARY_PATH=$LITE_HOME/runtime/lib:$LITE_HOME/runtime/third_party/dnnl:$LITE_HOME/tools/converter/lib:$LD_LIBRARY_PATH
```

### 1.2 OpenCV 安装

MindOCR中使用的OpenCV的so文件为mindspore-lite中自带的，由于mindspore-lite中没有OpenCV的头文件，因此需要额外引入。

下载[OpenCV源码](https://codeload.github.com/opencv/opencv/zip/refs/tags/4.5.2)。然后执行下面的操作解压安装OpenCV。

```shell
# 解压文件
unzip opencv-4.5.2.zip

# cmake 配置
cd opencv-4.5.2
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Release ..
make -j16
# 安装到制定路径
make install DESTDIR=/opencv_home
```

设置环境变量 ```OPENCV_HOME```

```shell
export OPENCV_HOME=/opencv_home
```

## 2. 代码下载与构建

```shell
# 下载代码
git clone https://github.com/mindspore-lab/mindocr.git
# 切换到制定路径
cd mindocr/deploy/cpp_infer_ddl/src
# 执行构建脚本
bash build.sh
```

构建完成后再 ```dist``` 路径下生成可执行文件

## 3. OCR识别测试
执行推理
```shell
./dist/infer \
   --input_image_dir /path_to_image_path \
   --backend lite \
   --det_model_path /path_to_det_model_path \
   --rec_model_path /path_to_rec_model_path \
   --character_dict_path /path_to_character_dict_path \
   --res_save_dir det_cls_rec
```

* input_image_dir 待识别的图片
* backend 推理引擎，设置为lite
* det_model_path 检测模型路径
* rec_model_path 识别模型路径
* character_dict_path 识别模型需要的字典文件
* res_save_dir OCR识别结果输出路径
