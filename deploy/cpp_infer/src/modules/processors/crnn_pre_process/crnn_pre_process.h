#ifndef MODULES_CRNN_PRE_PROCESS_H
#define MODULES_CRNN_PRE_PROCESS_H
#include <memory>
#include <utility>
#include <vector>
#include "module_manager/module_manager.h"
#include "config_parser/config_parser.h"
#include "utils/utils.h"
#include "data_type/data_type.h"
#include "data_type/constant.h"
#include "profile/profile.h"
#include "Log/Log.h"

class CrnnPreProcess : public AscendBaseModule::ModuleBase {
 public:
  CrnnPreProcess();

  ~CrnnPreProcess() override;

  Status Init(CommandParser *options, const AscendBaseModule::ModuleInitArgs &initArgs) override;

  Status DeInit() override;

 protected:
  Status Process(std::shared_ptr<void> inputData) override;

 private:
  int stdHeight_ = 48;
  int recMinWidth_ = 320;
  int recMaxWidth_ = 2240;
  bool staticMethod_ = true;
  std::vector<std::pair<uint64_t, uint64_t>> gearInfo_;
  std::vector<uint64_t> batchSizeList_;

  Status ParseConfig(CommandParser *options);

  std::vector<uint32_t> GetCrnnBatchSize(uint32_t frameSize);

  int GetCrnnMaxWidth(const std::vector<cv::Mat> &frames, float maxWHRatio);

  uint8_t *PreprocessCrnn(const std::vector<cv::Mat> &frames, uint32_t batchSize, int maxResizedW, float maxWHRatio,
                          std::vector<ResizedImageInfo> *resizedImageInfos);

  void GetGearInfo(int maxResizedW, std::pair<uint64_t, uint64_t> *gear);

  TaskType taskType_;
};

MODULE_REGIST(CrnnPreProcess)

#endif
