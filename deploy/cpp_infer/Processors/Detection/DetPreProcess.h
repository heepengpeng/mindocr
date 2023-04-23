#ifndef DET_PRE_PRECOSS_H
#define DET_PRE_PRECOSS_H
#include "../../Framework//ModuleBase.h"
#include "../../StatusCode//StatusCode.h"
#include <vector>
namespace MindOCR
{
    class DetPreProcess : public MindOCR::ModuleBase
    {
    public:
        DetPreProcess();
        ~DetPreProcess();
        STATUS_CODE Init();
        STATUS_CODE DeInit();

    protected:
        STATUS_CODE Process(std::shared_ptr<void> inputData);

    private:
        std::vector<std::shared_ptr<void>> gearList;
        std::vector<std::shared_ptr<void>> maxDotGear;
    };
} // namespace MindOCR

#endif