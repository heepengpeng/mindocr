#include "ModuleInfer.h"

#include <memory>
#include <algorithm>
#include <set>

namespace MindOCR {
    STATUS_CODE MindOCR::Model::Init(InferEngine engineType, ContextInfo &contextInfo) {
        m_inferEngine = engineType;
        if (engineType == InferEngine::MindX) {
            m_Model.reset(new MindXModel(contextInfo));
        } else if (engineType == InferEngine::Lite) {
            m_Model.reset(new LiteModel(contextInfo));
        }
        Warmup();
    }

    STATUS_CODE MindOCR::Model::Infer(std::shared_ptr<void> &inputData, std::vector<std::shared_ptr<void>> &output) {
        return STATUS_FAILED;
    }

    std::shared_ptr<ShapeInfo> MindOCR::Model::GetShapeInfo() {
        std::vector<int64_t> shape = m_Model->GetInputShape();
        std::vector<std::vector<int>> gears = m_Model->GetGear();
        std::string modelPath = m_Model->GetModelPath();

        if (shape.size() != 4) {
            return nullptr;
        }
        int64_t batchSize = shape[0];
        int64_t channel = shape[1];
        int64_t height = shape[2];
        int64_t width = shape[3];

        if (channel != 3) {
            return nullptr;
        }

        if (std::find(shape.begin(), shape.end(), -1) == shape.end()) {
            std::shared_ptr<ShapeInfo> ret(new ShapeInfo{ShapeType::STATIC_SHAPE, batchSize, channel, height, width});
            return ret;
        }

        if (gears.empty()) {
            return nullptr;
        }

        std::vector<int64_t> batchSizList;
        std::vector<int64_t> heightList;
        std::vector<int64_t> widthList;
        if (batchSize == -1) {
            for (auto gear: gears) {
                batchSizList.push_back(gear[0]);
            }
        } else {
            batchSizList.push_back(batchSize);
        }

        if (height == -1) {
            for (auto gear: gears) {
                heightList.push_back(gear[2]);
            }
        } else {
            heightList.push_back(height);
        }

        if (width == -1) {
            for (auto gear: gears) {
                widthList.push_back(gear[3]);
            }
        } else {
            widthList.push_back(width);
        }

        std::set<int64_t> batchSizeSet(batchSizList.begin(), batchSizList.end());
        std::set<int64_t> heightSet(heightList.begin(), heightList.end());
        std::set<int64_t> widthSet(widthList.begin(), widthList.end());
        if (batchSizeSet.size() > 1 and heightSet.size() > 1 or widthSet.size() > 1) {
            return nullptr;
        }

        batchSize = batchSizList[0];

        //dynamic image size
        if (heightList.size() == 1) {
            std::fill_n(heightList.begin(), widthList.size(), heightList[0]);
        }

        if (widthList.size() == 1) {
            std::fill_n(widthList.begin(), heightList.size(), widthList[0]);
        }
        std::vector<std::pair<int64_t , int64_t>> hwList(heightList.size());
        std::transform(heightList.begin(), heightList.end(), widthList.begin(), widthList.begin(),
                       [](const int64_t &h, const int64_t &w) -> std::pair<int64_t, int64_t> {
                           return std::make_pair(h, w);
                       });
    }

    void MindOCR::Model::Warmup() {

    }
}