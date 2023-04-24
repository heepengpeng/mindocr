# MxBase 分析

## 使用的地方  总共 3.8k = 13人/天
### MxBase:MxInit() 初始化   0.3k
*  MxBase::Log::Init()
*  MxBase::DeviceManager::GetInstance()->InitDevices()
  * 检查 /lib/libmxbase.so 是否存在 (这个是咋来的)
  * aclInit()
  * aclrtGetDeviceCount()
  * 失败调用 aclFinalize()
### 类 MxBase:ImageProcessor 图像处理  0.3k
* Decode
  * MxBase::DeviceManager::GetInstance()->SetDevices()
    * InitDevices()
    * aclrtCreateContext() 或  aclrSetCurrentContext()
    * acldvppJpegDecodeAsync 或 aclvppJpegDecoderAsync
### 类 MxBase:Model 模型   2k
* Model::Model(string &modelPath, int32_t deviceId)
  * InitModel()
    * MxBase::DeviceManager::GetInstance()->SetDevices()
    * aclrtCreateStream()
    * aclrtCreateConfigHandle()
    * aclmdLoadWithConfig()
    * aclmdlDestroyConfigHandle()
  * GetModelInputDesc()
    * aclmdGetNumInputs()
    * aclmdGetInputDims() / aclmdGetInputDimsV2()
    * aclmdGetInputDataType()
    * aclmdGetInputFormat()
  * GetDynamicDesc()
    * aclGetDynamicBatch()
    * aclGetDynamicHW()
    * aclGetDynamicGearCount()
    * aclGetDynamicDims()
    * aclmdGetInputIndexByName()
* Infer(vector<Tensor>& inputTensors)
  * SetDevice()
    * aclrtCreateContext() 或  aclrSetCurrentContext()
  * SetInputTensors()
    * aclrtMemory()
  * checkInputType()
    * aclrtGetInputDataType()
  * ModelInference()
    * aclmdlCreateDataset(),aclCreateDataBuffer(), aclmdlAddDatasetBuffer()
    * aclmdSetDynamicBatchSize()
    * aclmdlExecuteAsync(modelId_,inputDataset, outputDataset, stream_)
    * aclrtSyncronizeStream()
    * aclDestroyDataBuffer()

### MxBase:Tensor 张量  0.5k
* std::shared_ptr<void> data
### MxBase:TensorDType 张量类型  枚举类 0.1k
### MxBase:Image 图片类 0.4k
* std::shared_ptr<uint8_t> imageData_
### MxBase:ImageFormat::RGB_888 图片格式 0.1k
### MxBase:Size 大小 0.1k
* uint32_t width
* uint32_t height
