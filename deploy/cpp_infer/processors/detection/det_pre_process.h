#ifndef DET_PRE_PRECOSS_H
#define DET_PRE_PRECOSS_H
#include "../../framework/module_base.h"
#include "../../error_code/error_code.h"
#include <vector>
namespace MindOCR
{
    class DetPreProcess : public MindOCR::ModuleBase
    {
    public:
        DetPreProcess();
        ~DetPreProcess();
        APP_ERROR Init();
        APP_ERROR DeInit();

    protected:
        APP_ERROR Process(std::shared_ptr<void> inputData);

    private:
        std::vector<std::shared_ptr<void>> gearList;
        std::vector<std::shared_ptr<void>> maxDotGear;
    };
} // namespace MindOCR

#endif