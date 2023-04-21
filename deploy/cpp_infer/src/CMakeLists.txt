cmake_minimum_required(VERSION 3.10.2)
project(OcrDemo)
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
add_definitions(-Dgoogle=mindxsdk_private)

set(PROJECT_SRC_ROOT ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_MODULE_PATH ${PROJECT_SRC_ROOT}/CMake)
set(CMAKE_SKIP_BUILD_RPATH True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SRC_ROOT}/dist)
add_compile_options(-std=c++14 -fPIE -fstack-protector-all -Wall)
add_definitions(-DENABLE_DVPP_INTERFACE)

set(AscendBaseFolder ${PROJECT_SRC_ROOT}/ascend_base)

# Find ascendbase
set(ASCEND_BASE_DIR ${AscendBaseFolder})
get_filename_component(ASCEND_BASE_ABS_DIR ${ASCEND_BASE_DIR} ABSOLUTE)

file(GLOB_RECURSE ASCEND_BASE_SRC_FILES
		${ASCEND_BASE_ABS_DIR}/blocking_queue/*cpp
		${ASCEND_BASE_ABS_DIR}/config_parser/*cpp
		${ASCEND_BASE_ABS_DIR}/framework/module_manager/*cpp
		${ASCEND_BASE_ABS_DIR}/command_parser/*cpp
		)

# Find Header
set(HEADER_FILE_DIR
		${ASCEND_BASE_ABS_DIR}
		${ASCEND_BASE_ABS_DIR}/framework
		${PROJECT_SRC_ROOT}/modules
		${PROJECT_SRC_ROOT}/modules/crnn_post
		${PROJECT_SRC_ROOT}/modules/dbnet_post
		${PROJECT_SRC_ROOT}/modules/processors
		${PROJECT_SRC_ROOT}/modules/profile
		${PROJECT_SRC_ROOT}/modules/utils
		)
include_directories(${HEADER_FILE_DIR})

# Find Src
file(GLOB_RECURSE SRC_FILE
		${PROJECT_SRC_ROOT}/modules/crnn_post/*.cpp
		${PROJECT_SRC_ROOT}/modules/dbnet_post/*.cpp
		${PROJECT_SRC_ROOT}/modules/processors/dbnet_pre_process/*.cpp
		${PROJECT_SRC_ROOT}/modules/processors/dbnet_infer_process/*.cpp
		${PROJECT_SRC_ROOT}/modules/processors/dbnet_post_process/*.cpp
		${PROJECT_SRC_ROOT}/modules/processors/cls_pre_process/*.cpp
		${PROJECT_SRC_ROOT}/modules/processors/cls_infer_process/*.cpp
		${PROJECT_SRC_ROOT}/modules/processors/cls_post_process/*.cpp
		${PROJECT_SRC_ROOT}/modules/processors/crnn_pre_process/*.cpp
		${PROJECT_SRC_ROOT}/modules/processors/crnn_infer_process/*.cpp
		${PROJECT_SRC_ROOT}/modules/processors/crnn_post_process/*.cpp
		${PROJECT_SRC_ROOT}/modules/processors/collect_process/*.cpp
		${PROJECT_SRC_ROOT}/modules/processors/hand_out_process/*.cpp
		${PROJECT_SRC_ROOT}/modules/profile/*.cpp
		${PROJECT_SRC_ROOT}/modules/utils/*.cpp
		${PROJECT_SRC_ROOT}/main.cpp
		)

set(SOURCE_FILE
		${SRC_FILE}
		${ASCEND_BASE_SRC_FILES})

set(MX_SDK_HOME $ENV{MX_SDK_HOME})
set(ASCEND_HOME_PATH $ENV{ASCEND_HOME_PATH})
set(ARCH_PATTERN $ENV{ARCH_PATTERN})
set(LITE_HOME $ENV{LITE_HOME})
include_directories(
		${MX_SDK_HOME}/include
		${MX_SDK_HOME}/opensource/include
		${MX_SDK_HOME}/opensource/include/opencv4
		${MX_SDK_HOME}/include/MxBase
		${ASCEND_HOME_PATH}/${ARCH_PATTERN}/include
		${ASCEND_HOME_PATH}/${ARCH_PATTERN}/runtime/include
		${LITE_HOME}/runtime/
)

link_directories(
		${MX_SDK_HOME}/lib
		${MX_SDK_HOME}/lib/modelpostprocessors
		${MX_SDK_HOME}/include
		${MX_SDK_HOME}/opensource/lib
		${ASCEND_HOME_PATH}/atc/lib64
		${LITE_HOME}/runtime/lib
		${LITE_HOME}/tools/converter/lib
)
include_directories(/usr/local/Ascend/latest/runtime/include)
# Set the target executable file
add_executable(infer ${SOURCE_FILE})
target_link_libraries(infer  gflags /usr/local/Ascend/latest/runtime/lib64/libascendcl.so)
target_link_libraries(infer mindspore-lite dl ascendcl acl_dvpp opencv_world mxbase cpprest glog pthread securec -Wl,-z,relro,-z,now,-z,noexecstack -pie -s)
