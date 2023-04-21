#ifndef MODULES_DBNET_INFER_PROCESS_H
#define MODULES_DBNET_INFER_PROCESS_H
#include <memory>
#include "module_manager/module_base.h"
#include "config_parser/config_parser.h"
#include "data_type/data_type.h"
#include "profile/profile.h"
#include "MxBase/MxBase.h"
#include "Log/Log.h"

class DbnetInferProcess : public AscendBaseModule::ModuleBase {
 public:
  DbnetInferProcess();

  ~DbnetInferProcess() override;

  Status Init(CommandParser *options, const AscendBaseModule::ModuleInitArgs &initArgs) override;

  Status DeInit() override;

 protected:
  Status Process(std::shared_ptr<void> inputData) override;

 private:
  int32_t deviceId_ = 0;
  std::unique_ptr<MxBase::Model> dbNetMindX_{};
  mindspore::Model *dbNetLite_{};
  BackendType backend_;

  Status ParseConfig(CommandParser *options, const AscendBaseModule::ModuleInitArgs &initArgs);

  Status MindXModelInfer(std::shared_ptr<CommonData> data);

  Status LiteModelInfer(std::shared_ptr<CommonData> data);
};

MODULE_REGIST(DbnetInferProcess)

#endif
