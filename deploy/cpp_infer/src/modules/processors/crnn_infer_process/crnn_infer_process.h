#ifndef MODULES_CRNN_INFER_PROCESS_H
#define MODULES_CRNN_INFER_PROCESS_H

#include <vector>
#include <memory>
#include "crnn_post/crnn_post.h"
#include "module_manager/module_manager.h"
#include "config_parser/config_parser.h"
#include "data_type/data_type.h"
#include "profile/profile.h"
#include "MxBase/MxBase.h"
#include "Log/Log.h"

class CrnnInferProcess : public AscendBaseModule::ModuleBase {
 public:
  CrnnInferProcess();

  ~CrnnInferProcess() override;

  Status Init(CommandParser *options, const AscendBaseModule::ModuleInitArgs &initArgs) override;

  Status DeInit() override;

 protected:
  Status Process(std::shared_ptr<void> inputData) override;

 private:
  int stdHeight_ = 48;
  int32_t deviceId_ = 0;
  bool staticMethod_ = true;
  std::vector<MxBase::Model *> crnnNetMindX_;
  std::vector<LiteModelWrap *> crnnNetLite_;
  std::vector<uint32_t> batchSizeList_;
  BackendType backend_;

  Status ParseConfig(CommandParser *options, const AscendBaseModule::ModuleInitArgs &initArgs);

  Status MindXModelInfer(const std::shared_ptr<CommonData> &data);

  Status LiteModelInfer(const std::shared_ptr<CommonData> &data);
};

MODULE_REGIST(CrnnInferProcess)

#endif
