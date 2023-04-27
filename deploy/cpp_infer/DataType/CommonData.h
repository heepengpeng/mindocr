#ifndef PROCESS_DATA_H
#define PROCESS_DATA_H

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "DataUtils.h"
#include <tuple>
template<typename T>
struct CommonData {
    // modules info
    int channelId = {};
    int imageId = {};
    int imageTotal = {};
    int subImageTotal = {};


    // imageInfo
    std::string imagePath = {};
    std::string imageName = {};
    uint32_t srcWeight = {};
    uint32_t srcHeight = {};
    cv::Mat frame = {};
    std::vector<cv::Mat> imageMatVec = {};

    //infer related
    uint8_t *imageBuf = {};
    std::vector<T> outputTensorVec = {};
    std::vector<ResizedImageInfo> resizedImageInfos = {};

    //det info
    uint32_t resizeWidth = {};
    uint32_t resizeHeight = {};
    float ratio = {};

    // cls and rec
    uint32_t batchSize = {};
    uint32_t frameSize = {};
    bool eof = {};

    // rec
    int maxResizedW = {};
    float maxWHRatio = {};

    //infer res
    std::string saveFileName = {};
    std::vector<std::string> inferRes = {};
};

struct StopData {
    bool skip = true;
    int image_total = 0;
};

struct ContextInfo {
    const char *modelPath;
    uint8_t deviceId;
};

enum InferEngine {
    MindX = 0,
    Lite = 1
};
enum ShapeType {
    STATIC_SHAPE = 0,
    DYNAMIC_SHAPE = 1,
    DYNAMIC_BATCHSIZE = 2,
    DYNAMIC_IMAGESIZE = 3,
};

struct ShapeInfo {
    ShapeType shapeType;
    int64_t batchSize;
    int64_t channel;
    int64_t height;
    int64_t width;
};

#endif