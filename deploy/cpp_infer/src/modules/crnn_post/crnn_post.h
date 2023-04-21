#ifndef MODULES_CRNN_POST_H
#define MODULES_CRNN_POST_H
#include <string>
#include <algorithm>
#include <vector>
#include <memory>
#include "utils/utils.h"

class CrnnPost {
 public:
  CrnnPost();

  ~CrnnPost() = default;

  void ClassNameInit(const std::string &fileName);

  std::string GetClassName(size_t classId);

  void CalcMindXOutputIndex(const int64_t *resHostBuf,
                            size_t batchSize,
                            size_t objectNum,
                            std::vector<std::string> *resVec);

  void CalcLiteOutputIndex(const int32_t *resHostBuf,
                           size_t batchSize,
                           size_t objectNum,
                           std::vector<std::string> *resVec);

 private:
  std::vector<std::string> labelVec_ = {};  // labels info
  uint32_t classNum_ = 0;
  uint32_t objectNum_ = 200;
  uint32_t batchSize_ = 0;
  uint32_t blankIdx_ = 0;
};

#endif
