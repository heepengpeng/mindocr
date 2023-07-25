#include "include/mslite_inference.h"
#include "include/utility.h"

using namespace mindspore_infer;
namespace mslite_infer {
    std::shared_ptr<Predictor> CreatePredictor(const Config &config) {
      auto predictor = make_shared<Predictor>(config);
      predictor->InitModel();
      return predictor;
    }

    Predictor::Predictor(const mslite_infer::Config &config) {
      this->config = config;
    }

    int Predictor::InitModel() {
      if (this->CreateContext() != 0) {
        return -1;
      }

      this->model = new mindspore::Model();
      mindspore::Status ret = mindspore::kLiteParamInvalid;
      if (Utility::endswith(config.model_path, ".mindir")) {
        ret = this->model->Build(config.model_path, mindspore::kMindIR, this->context);
      } else if (Utility::endswith(config.model_path, ".ms")) {
        ret = this->model->Build(config.model_path, mindspore::kMindIR_Lite, this->context);
      }

      if (ret != mindspore::kSuccess) {
        std::cerr << "Load MindSpore Lite Model failed." << std::endl;
        return -1;
      }

      return 0;
    }

    int Predictor::CreateContext() {
      this->context = std::make_shared<mindspore::Context>();
      if (context == nullptr) {
        std::cerr << "New MindSpore Lite context failed." << std::endl;
        return -1;
      }

      auto &device_list = context->MutableDeviceInfo();
      auto device_info = std::make_shared<mindspore::CPUDeviceInfo>();

      if (device_info == nullptr) {
        std::cerr << "New MindSpore Lite CPUDeviceInfo failed." << std::endl;
        return -1;
      }

      if (this->config.precision == "fp16") {
        device_info->SetEnableFP16(true);
      }

      device_list.push_back(device_info);

      this->context->SetThreadNum(this->config.thread_num);

      return 0;
    }

    int Predictor::Predict(const std::vector<std::vector<float>> &inputs,
                           const std::vector<std::vector<int64_t>> &inputs_shape,
                           std::vector<std::vector<float>> &outputs, std::vector<std::vector<int64_t>> &outputs_shape) {

      auto model_inputs = this->model->GetInputs();

      if (this->model->Resize(model_inputs, inputs_shape) != mindspore::kSuccess) {
        std::cerr << "MindSpore Lite Resize failed." << std::endl;
        return -1;
      }

      auto input_num = model_inputs.size();
      for (size_t i = 0; i < input_num; i++) {
        model_inputs[i].SetData(const_cast<float *>(inputs[i].data()), true);
      }

      std::vector<mindspore::MSTensor> model_outputs;
      std::cout << "start model Predict" << std::endl;
      auto result = this->model->Predict(model_inputs, &model_outputs);
      std::cout << "end model Predict" << std::endl;
      if (result != mindspore::kSuccess) {
        std::cerr << "MindSpore Lite Predict failed." << std::endl;
        return -1;
      }

      outputs_shape.clear();
      outputs.clear();

      for (const auto &model_output: model_outputs) {
        outputs_shape.emplace_back(model_output.Shape());

        auto data_size = model_output.DataSize();
        auto data_ptr = model_output.Clone()->Data().get();
        std::vector<float> output(model_output.ElementNum());
        auto ret = memcpy_s(output.data(), data_size, data_ptr, data_size);
        if (ret) {
          std::cerr << "MindSpore Lite Predict output memcpy_s failed." << std::endl;
          return -1;
        }

        outputs.emplace_back(output);
      }

      for (size_t i = 0; i < input_num; i++) {
        model_inputs[i].SetData(nullptr);
      }

      return 0;
    }
}
