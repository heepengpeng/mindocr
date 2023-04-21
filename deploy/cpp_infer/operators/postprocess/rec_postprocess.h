#include <string>
#include "opencv2/core.hpp"
#include "../../status_code/status_code.h"
namespace MindOCR
{
    class RecCTCLabelDecode
    {
    public:
        RecCTCLabelDecode(){};
        ~RecCTCLabelDecode(){};
        STATUS_CODE Init(const std::string character_dict_path);
        STATUS_CODE Run(cv::Mat &preds, std::vector<std::string> &texts);
    };

};