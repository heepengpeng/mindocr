#ifndef MODULES_DBNET_PRE_PROCESS_H
#define MODULES_DBNET_PRE_PROCESS_H
#include <memory>
#include <string>
#include <vector>
#include <utility>
#include "module_manager/module_manager.h"
#include "config_parser/config_parser.h"
#include "data_type/data_type.h"
#include "utils/utils.h"
#include "profile/profile.h"
#include "Log/Log.h"

class DbnetPreProcess : public AscendBaseModule::ModuleBase {
 public:
  DbnetPreProcess();

  ~DbnetPreProcess() override;

  Status Init(CommandParser *options, const AscendBaseModule::ModuleInitArgs &initArgs) override;

  Status DeInit() override;

 protected:
  Status Process(std::shared_ptr<void> inputData) override;

 private:
  std::string deviceType_;
  int32_t deviceId_ = 0;

  std::unique_ptr<MxBase::ImageProcessor> imageProcessor_{};
  uint64_t maxH_ = 0;
  uint64_t maxW_ = 0;

  std::pair<uint64_t, uint64_t> maxDotGear_;

  std::vector<float> mean_ = {0.485f, 0.456f, 0.406f};
  std::vector<float> scale_ = {1 / 0.229f, 1 / 0.224f, 1 / 0.225f};

  std::vector<std::pair<uint64_t, uint64_t>> gearInfo_;

  Status ParseConfig(CommandParser *options);

  void GetMatchedGear(const cv::Mat &inImg, std::pair<uint64_t, uint64_t> *gear);

  void Resize(const cv::Mat &inImg, cv::Mat *outImg, const std::pair<uint64_t, uint64_t> &gear, float *inputRatio);

  void Padding(cv::Mat *inImg, const std::pair<uint64_t, uint64_t> &gear);

  void NormalizeByChannel(std::vector<cv::Mat> *bgrChannels);
};

MODULE_REGIST(DbnetPreProcess)

#endif
