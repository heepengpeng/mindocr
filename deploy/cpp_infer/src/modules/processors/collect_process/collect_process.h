#ifndef MODULES_COLLECT_PROCESS_H
#define MODULES_COLLECT_PROCESS_H

#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include "module_manager/module_manager.h"
#include "config_parser/config_parser.h"
#include "profile/profile.h"
#include "data_type/data_type.h"
#include "Log/Log.h"

class CollectProcess : public AscendBaseModule::ModuleBase {
 public:
  CollectProcess();

  ~CollectProcess() override;

  Status Init(CommandParser *options, const AscendBaseModule::ModuleInitArgs &initArgs) override;

  Status DeInit() override;

 protected:
  Status Process(std::shared_ptr<void> inputData) override;

 private:
  std::string resultPath_;
  std::unordered_map<int, int> idMap_;
  int inferSize_ = 0;
  TaskType taskType_;
  std::string saveFileName_;

  Status ParseConfig(CommandParser *options);

  void SignalSend(int imgTotal);

  static std::string GenerateDetClsRecInferRes(const std::string &imageName, uint32_t frameSize,
                                               const std::vector<std::string> &inferRes);

  static std::string GenerateDetInferRes(const std::string &imageName, const std::vector<std::string> &inferRes);

  static std::string GenerateClsInferRes(const std::string &imageName, const std::vector<std::string> &inferRes);

  static std::string GenerateRecInferRes(const std::string &imageName, const std::vector<std::string> &inferRes);
};

MODULE_REGIST(CollectProcess)

#endif
