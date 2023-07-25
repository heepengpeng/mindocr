if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

PROJECT(mindocr CXX)
cmake_minimum_required(VERSION 3.14)
set(PROJECT_SRC_ROOT ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SRC_ROOT}/dist)
add_definitions(-D_GLIBCXX_USE_CXX14_ABI=0)
add_compile_options(-std=c++14 -fPIE -fno-stack-protector -Wall)

set(LITE_HOME E:\\001MindOCRWindows\\mindspore-lite-2.0.0-win-x64)
set(OPENCV_DIR E:\\001MindOCRWindows\\OpenCV-MinGW-Build-OpenCV-3.4.8-x64)

set(LITE_HOME ${LITE_HOME})
include_directories(${LITE_HOME}/runtime)
link_directories(${LITE_HOME}/runtime/lib ${LITE_HOME}/tools/converter/lib)

set(OpenCV_DIR ${OPENCV_DIR})
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(third_party/gflags-2.2.2)
add_subdirectory(third_party/json-3.11.2)
include_directories("${CMAKE_SOURCE_DIR}/")

set(DEPS ${DEPS} ${OpenCV_LIBS} gflags::gflags nlohmann_json::nlohmann_json)
set(DEPS ${DEPS} ssp -Wl,--whole-archive mindspore-lite -Wl,--no-whole-archive pthread mindspore_glog -g)

AUX_SOURCE_DIRECTORY(./src SRCS)

add_executable(infer main.cpp ${SRCS})
target_link_libraries(infer ${DEPS})
