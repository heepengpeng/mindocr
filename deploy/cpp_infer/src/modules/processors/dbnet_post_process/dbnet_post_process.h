#ifndef MODULES_DBNET_POST_PROCESS_H
#define MODULES_DBNET_POST_PROCESS_H
#include <memory>
#include <string>
#include "module_manager/module_manager.h"
#include "config_parser/config_parser.h"
#include "data_type/data_type.h"
#include "profile/profile.h"
#include "Log/Log.h"
#include "utils/utils.h"

class DbnetPostProcess : public AscendBaseModule::ModuleBase {
 public:
  DbnetPostProcess();

  ~DbnetPostProcess() override;

  Status Init(CommandParser *options, const AscendBaseModule::ModuleInitArgs &initArgs) override;

  Status DeInit() override;

 protected:
  Status Process(std::shared_ptr<void> inputData) override;

 private:
  std::string resultPath_;
  std::string nextModule_;

  Status ParseConfig(CommandParser *options);

  static float CalcCropWidth(const TextObjectInfo &textObject);

  static float CalcCropHeight(const TextObjectInfo &textObject);
};

MODULE_REGIST(DbnetPostProcess)

#endif
