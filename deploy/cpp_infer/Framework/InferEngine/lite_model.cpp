#include "lite_model.h"
#include "../../utils/SafeUtils.h"

namespace MindOCR {

    LiteModel::LiteModel() {}

    STATUS_CODE LiteModel::Infer(std::shared_ptr<void> inputData, std::vector <MSTensor> &output) {

    }

    STATUS_CODE LiteModel::Init(ContextInfo &contextInfo) {
        m_contextInfo = contextInfo;
        SafeUtils::checkValidFile(m_contextInfo.modelPath);
        InitModel();
    }

    STATUS_CODE LiteModel::InitModel() {
        size_t size = 0;
        char* model_buf = SafeUtils::ReadFile(m_contextInfo.modelPath, &size);
        if (model_buf == nullptr) {
            LogError << "Read model file failed." << std::endl;
            return MindOCR::FAILED;
        }
        auto context = std::make_shared<mindspore::Context>();
        if (context == nullptr) {
            delete[] (model_buf);
            LogError << "New context failed." << std::endl;
            return MindOCR::FAILED;
        }
        auto &device_list = context->MutableDeviceInfo();
        auto deviceInfo = std::make_shared<mindspore::CPUDeviceInfo>();
        deviceInfo->set
    }
}