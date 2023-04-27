#ifndef DECODE_PRECOSS_H
#define DECODE_PRECOSS_H
#include "../../framework/ModuleBase.h"
#include "../../StatusCode/StatusCode.h"
namespace MindOCR
{
    class DecodeProcess : public MindOCR::ModuleBase
    {
    public:
        DecodeProcess();
        ~DecodeProcess();
        STATUS_CODE Init();
        STATUS_CODE DeInit();

    protected:
        uint8_t Process(std::shared_ptr<void> inputData);
    };
} // namespace MindOCR

#endif