#ifndef DEPLOY_CPP_INFER_SRC_PARALLEL_MODULE_DETECTION_DET_INFER_NODE_H_
#define DEPLOY_CPP_INFER_SRC_PARALLEL_MODULE_DETECTION_DET_INFER_NODE_H_
#include <memory>
#include "framework/module_base.h"
#include "config_parser/config_parser.h"
#include "data_type/data_type.h"
#include "profile/profile.h"
//#include "Log/Log.h"
#include "framework/module_factory.h"

class DetInferNode : public AscendBaseModule::ModuleBase {
 public:
  DetInferNode();

  ~DetInferNode() override;

  Status Init(CommandParser *options, const AscendBaseModule::ModuleInitArgs &initArgs) override;

  Status DeInit() override;

 protected:
  Status Process(std::shared_ptr<void> inputData) override;

 private:
  int32_t deviceId_ = 0;
  mindspore::Model *dbNetLite_{};
  BackendType backend_;

  Status ParseConfig(CommandParser *options, const AscendBaseModule::ModuleInitArgs &initArgs);

  Status LiteModelInfer(std::shared_ptr<CommonData> data);
};

MODULE_REGIST(DetInferNode)

#endif
