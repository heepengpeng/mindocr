#ifndef MODULES_CRNN_POST_PROCESS_H
#define MODULES_CRNN_POST_PROCESS_H

#include <unordered_set>
#include <memory>
#include <string>
#include <vector>
#include "crnn_post/crnn_post.h"
#include "module_manager/module_manager.h"
#include "config_parser/config_parser.h"
#include "profile/profile.h"
#include "data_type/data_type.h"
#include "MxBase/MxBase.h"
#include "Log/Log.h"

class CrnnPostProcess : public AscendBaseModule::ModuleBase {
 public:
  CrnnPostProcess();

  ~CrnnPostProcess() override;

  Status Init(CommandParser *options, const AscendBaseModule::ModuleInitArgs &initArgs) override;

  Status DeInit() override;

 protected:
  Status Process(std::shared_ptr<void> inputData) override;

 private:
  CrnnPost crnnPost_;
  std::string recDictionary_;
  std::string resultPath_;

  std::unordered_set<int> idSet_;

  Status ParseConfig(CommandParser *options);

  Status PostProcessMindXCrnn(uint32_t framesSize, const std::vector<MxBase::Tensor> &inferOutput,
                              std::vector<std::string> *textsInfos);

  Status PostProcessLiteCrnn(uint32_t framesSize, const std::vector<mindspore::MSTensor> &inferOutput,
                             std::vector<std::string> *textsInfos);
};

MODULE_REGIST(CrnnPostProcess)

#endif
