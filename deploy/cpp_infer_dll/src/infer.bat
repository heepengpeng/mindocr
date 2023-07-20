

set LITE_HOME=E:/001MindOCRWindows/mindspore-lite-2.0.0-win-x64
set OPENCV_DIR=E:/001MindOCRWindows/OpenCV-MinGW-Build-OpenCV-3.4.8-x64

set PATH=%LITE_HOME%/runtime/lib;%LITE_HOME%/runtime/third_party/dnnl;%LITE_HOME%/tools/converter/lib;%LITE_HOME%/tools/converter/converter;%PATH%
set PATH=%OPENCV_DIR%/x64/mingw/lib;%PATH%

cd dist
infer.exe --input_images_dir D:/data/img --det_model_path D:/data/ch_ppocr_server_v2.0_det_infer_cpu.ms --rec_model_path D:/data/ch_ppocr_server_v2.0_rec_infer_argmax_cpu.ms --character_dict_path D:/data/ppocr_keys_v1.txt --res_save_dir det_rec
cd ..
