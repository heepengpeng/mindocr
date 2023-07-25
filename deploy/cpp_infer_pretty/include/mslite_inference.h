#ifndef MSLITE_INFERENCE_H
#define MSLITE_INFERENCE_H

#include <string>
#include <vector>
#include <memory>
#include "opencv2/opencv.hpp"
#include "include/api/model.h"

using namespace std;

namespace mslite_infer {
    struct Config {
        string model_path;
        string device;
        string precision;
        int thread_num;
    };

    class Predictor {
    public:
        Predictor() = delete;

        ~Predictor() = default;

        explicit Predictor(const Config &config);

        int InitModel();

        int
        Predict(const std::vector<std::vector<float>> &inputs, const std::vector<std::vector<int64_t>> &inputs_shape,
                std::vector<std::vector<float>> &outputs, std::vector<std::vector<int64_t>> &outputs_shape);

    private:
        int CreateContext();

        std::shared_ptr<mindspore::Context> context;
        mindspore::Model * model;
        Config config;
    };

    std::shared_ptr<Predictor> CreatePredictor(const Config &config);
}

#endif //MSLITE_INFERENCE_H
