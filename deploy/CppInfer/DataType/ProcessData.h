#ifndef PROCESS_DATA_H
#define PROCESS_DATA_H

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

struct ProcessData {
    int sub_image_total = 0;
    int image_total = 0;
    std::vector<int> infer_result;
    bool skip = false;
    std::string image_path = "";
    std::string image_name = "";
    int image_id = 0;
    cv::Mat frame;
    int original_width = 0;
    int original_height = 0;
    int resize_h = 0;
    int resize_w = 0;
    std::vector <cv::Mat> sub_image_list;
    int sub_image_size = 0;
    cv::Mat input_array;
    cv::Mat output_array;
    float max_wh_ratio = 0.0;
};

struct StopData {
    bool skip = true;
    int image_total = 0;
};

struct ContextInfo {
    InferEngine engineType;
    std::string modelPath;
    uint8_t deviceId;
};

#endif