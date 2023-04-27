#include "LiteModel.h"

namespace MindOCR {

    std::vector<MSTensor> LiteModel::Infer(uint8_t *srcData, uint32_t batchSize, int64_t height, int64_t width) {


        auto inputs = m_model->GetInputs();

        std::vector<std::vector<int64_t>> dims;
        std::vector<int64_t> shape;
        shape.push_back(batchSize);
        shape.push_back(3); // channel
        shape.push_back(height);
        shape.push_back(width);
        dims.push_back(shape);

        m_model->Resize(inputs, dims);
        inputs[0].SetData(srcData);

        std::vector<MSTensor> outputs;
        auto status = m_model->Predict(inputs, &outputs);
        if (status != mindspore::kSuccess) {
            std::cerr << "Inference error." << std::endl;
            return outputs;
        }
        return outputs;
    }


    STATUS_CODE LiteModel::Init() {
        size_t size = 0;
        // read model file
        char *model_buf = SafeUtils::ReadFile(m_contextInfo.modelPath, &size);
        if (model_buf == nullptr) {
            std::cerr << "Read model file failed." << std::endl;
            return STATUS_CODE::STATUS_FAILED;
        }

        // init context
        auto context = std::make_shared<mindspore::Context>();
        if (context == nullptr) {
            delete[] (model_buf);
            std::cerr << "New context failed." << std::endl;
            return STATUS_CODE::STATUS_FAILED;
        }

        // set Ascend device first
        auto &device_list = context->MutableDeviceInfo();
        auto ascend_device_info = std::make_shared<mindspore::Ascend310DeviceInfo>();
        if (ascend_device_info == nullptr) {
            std::cerr << "New Ascend310DeviceInfo failed." << std::endl;
        }
        ascend_device_info->SetDeviceID(m_contextInfo.deviceId);
        device_list.push_back(ascend_device_info);

        // set CPU device after Ascend as second choice
        auto cpu_device_info = std::make_shared<mindspore::CPUDeviceInfo>();
        cpu_device_info->SetEnableFP16(true);
        if (cpu_device_info == nullptr) {
            delete[] (model_buf);
            std::cerr << "New CPUDeviceInfo failed." << std::endl;
            return STATUS_CODE::STATUS_FAILED;
        }
        device_list.push_back(ascend_device_info);

        // create model
        m_model.reset(new(std::nothrow) mindspore::Model());
        if (m_model == nullptr) {
            delete[] (model_buf);
            std::cerr << "New Model failed." << std::endl;
            return STATUS_CODE::STATUS_FAILED;
        }

        // build model
        auto build_ret = m_model->Build(model_buf, size, mindspore::kMindIR, context);
        delete[] (model_buf);
        if (build_ret != mindspore::kSuccess) {
            std::cerr << "Build model error " << std::endl;
            return STATUS_CODE::STATUS_FAILED;
        }
        // shape before resize
        m_shape = m_model->GetInputs()[0].Shape();
        return STATUS_CODE::STATUS_SUCCESS;
    }

    std::vector<int> LiteModel::GetShape() {
        return m_shape;
    }

    std::vector<std::vector<int>> LiteModel::GetGear() {
        std::vector<std::vector<int>> gears;
        std::ifstream file_stream(m_contextInfo.modelPath, std::ios::binary);
        std::string content((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());

        std::regex pattern(R"(_all_origin_gears_inputs.*?\xa0)");
        std::smatch match;
        if (std::regex_search(content, match, pattern)) {
            std::string matchText = match[0].str();


            std::smatch results;
            std::string::const_iterator iterStart = matchText.begin(); //迭代器声明
            std::string::const_iterator iterEnd = matchText.end();
            std::string temp;
            std::regex shapePattern(R"(:4:(\d+),(\d+),(\d+),(\d+))");

            while (std::regex_search(iterStart, iterEnd, results, shapePattern)) {
                temp = results[0];
                temp = temp.substr(3); // remove :4:
                std::vector<std::string> shapeVec = StringUtils::SplitString(temp, ',');
                std::vector<int> gear;
                for (auto s: shapeVec) {
                    gear.push_back(std::stoi(s));
                }
                gears.push_back(gear);
                iterStart = results[0].second;
            }
        }
        return gears;
    }

    LiteModel::LiteModel(ContextInfo &contextInfo) : m_contextInfo(contextInfo) {
    }

    std::vector<int64_t> LiteModel::GetInputShape() {
        return m_shape;
    }

    std::string LiteModel::GetModelPath() {
        return m_contextInfo.modelPath;
    }

}