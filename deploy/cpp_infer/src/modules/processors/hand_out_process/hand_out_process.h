#ifndef MODULES_HANDOUT_PROCESS_H
#define MODULES_HANDOUT_PROCESS_H
#include <string>
#include <memory>
#include "module_manager/module_manager.h"
#include "config_parser/config_parser.h"
#include "data_type/data_type.h"
#include "utils/utils.h"
#include "profile/profile.h"
#include "Log/Log.h"

class HandOutProcess : public AscendBaseModule::ModuleBase {
 public:
    HandOutProcess();

    ~HandOutProcess() override;

    Status Init(CommandParser *options, const AscendBaseModule::ModuleInitArgs &initArgs) override;

    Status DeInit() override;

 protected:
    Status Process(std::shared_ptr<void> inputData) override;

 private:
    int imgId_ = 0;
    std::string deviceType_;

    Status ParseConfig(CommandParser *options);

    std::string resultPath_;

    std::string nextModule_;

    BackendType backendType_;

    cv::Mat DecodeImgDvpp(std::string imgPath);

    std::unique_ptr<MxBase::ImageProcessor> imageProcessor_{};
};

MODULE_REGIST(HandOutProcess)

#endif
