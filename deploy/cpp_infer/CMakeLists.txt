cmake_minimum_required(VERSION 3.10.2)
project(OCRCppInfer)
add_executable(main infer.cpp Utils/DataUtils.h Utils/StringUtils.cpp Utils/StringUtils.h Framework/ModuleInfer.cpp)
find_package(OpenCV CONFIG REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/runtime/
        ${CMAKE_CURRENT_SOURCE_DIR}/BlockingQueue/
        ${CMAKE_CURRENT_SOURCE_DIR}/CommandParser/
        ${CMAKE_CURRENT_SOURCE_DIR}/DataType/
        ${CMAKE_CURRENT_SOURCE_DIR}/Framework/
        ${CMAKE_CURRENT_SOURCE_DIR}/Log/
        ${CMAKE_CURRENT_SOURCE_DIR}/Pipeline/
        ${CMAKE_CURRENT_SOURCE_DIR}/Processors/
        ${CMAKE_CURRENT_SOURCE_DIR}/StatusCode/
        ${CMAKE_CURRENT_SOURCE_DIR}/Utils/

)  # 添加头文件寻找路径
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/runtime/lib)  # 添加库文件寻找路径

target_link_libraries(main PRIVATE opencv_ml opencv_dnn opencv_core opencv_flann )