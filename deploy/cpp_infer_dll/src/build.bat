set LITE_HOME=E:/001MindOCRWindows/mindspore-lite-2.0.0-win-x64
set OPENCV_DIR=E:/001MindOCRWindows/OpenCV-MinGW-Build-OpenCV-3.4.8-x64

mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - MinGW Makefiles" ..
cmake --build .
cd ..
cp ./build/libocr.dll.a ./dist