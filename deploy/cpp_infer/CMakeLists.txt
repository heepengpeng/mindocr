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
        ${PROJECT_SRC_ROOT}/BlockingQueue
        ${PROJECT_SRC_ROOT}/CommandParser
        ${PROJECT_SRC_ROOT}/DataType
        ${PROJECT_SRC_ROOT}/Framework
        ${PROJECT_SRC_ROOT}/Framework/InferEngine
        ${PROJECT_SRC_ROOT}/Operators/Postprocess
        ${PROJECT_SRC_ROOT}/Operators/Preprocess
        ${PROJECT_SRC_ROOT}/Pipeline
        ${PROJECT_SRC_ROOT}/Processors/Classification
        ${PROJECT_SRC_ROOT}/Processors/Common
        ${PROJECT_SRC_ROOT}/Processors/Detection
        ${PROJECT_SRC_ROOT}/Processors/Recognition
        ${PROJECT_SRC_ROOT}/StatusCode
        )

include_directories(${HEADER_FILE_DIR})

#find src
file(GLOB_RECURSE SRC_FILE
        ${PROJECT_SRC_ROOT}/main.cpp
        )

add_executable(main ${SRC_FILE} Utils/SafeUtils.cpp Utils/SafeUtils.h CommandParser/CommandParser.h)

target_link_libraries(main, ascendcl acl_dvpp opencv_world mxbase cpprest glog pthread -Wl,-z,relro,-z,now,-z,noexecstack -pie -s)