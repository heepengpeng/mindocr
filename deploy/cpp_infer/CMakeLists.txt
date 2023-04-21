cmake_minimum_required(VERSION 3.10.2)
project(OCRCppInfer)
add_definition(-D_GLIBCXX_USE_CXX!!_ABI=0)
add_definitions(-Dgoogle=mindxsdk_private)

set(PROJECT_SRC_ROOT ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_MODULE_PATH ${PROJECT_SRC_ROOT}/CMake)
set(CMAKE_SKIP_BUILD_RPATH  True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SRC_ROOT}/dist)
add_compile_options(-std=c++11 -fPIE -fstack-protector-all -Wall)
add_definitions(-DENABLE_DVPP_INTERFACE)

# find header
set(HEADER_FILE_DIR
        ${PROJECT_SRC_ROOT}/blocking_queue
        ${PROJECT_SRC_ROOT}/data_type
        ${PROJECT_SRC_ROOT}/status_code
        ${PROJECT_SRC_ROOT}/framework
        ${PROJECT_SRC_ROOT}/framework/infer_engine
        ${PROJECT_SRC_ROOT}/operators/postprocess
        ${PROJECT_SRC_ROOT}/operators/preprocess
        ${PROJECT_SRC_ROOT}/pipeline
        ${PROJECT_SRC_ROOT}/processors/classification
        ${PROJECT_SRC_ROOT}/processors/common
        ${PROJECT_SRC_ROOT}/processors/detection
        ${PROJECT_SRC_ROOT}/processors/recognition
        )

include_directories(${HEADER_FILE_DIR})

#find src
file(GLOB_RECURSE SRC_FILE
        ${PROJECT_SRC_ROOT}/main.cpp
        )

add_executable(main ${SRC_FILE})

target_link_libraries(main, ascendcl acl_dvpp opencv_world mxbase cpprest glog pthread -Wl,-z,relro,-z,now,-z,noexecstack -pie -s)