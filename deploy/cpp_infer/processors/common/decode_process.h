#ifndef DECODE_PRECOSS_H
#define DECODE_PRECOSS_H
#include "../../framework/module_base.h"
#include "../../error_code/error_code.h"
namespace MindOCR
{
    class DecodeProcess : public MindOCR::ModuleBase
    {
    public:
        DecodeProcess();
        ~DecodeProcess();
        APP_ERROR Init();
        APP_ERROR DeInit();

    protected:
        uint8_t Process(std::shared_ptr<void> inputData);
    };
} // namespace MindOCR

#endif