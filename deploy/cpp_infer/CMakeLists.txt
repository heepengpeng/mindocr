cmake_minimum_required(VERSION 3.10.2)
project(OCRCppInfer)
add_definition(-D_GLIBCXX_USE_CXX!!_ABI=0)
add_definitions(-Dgoogle=mindxsdk_private)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_MODULE_PATH )