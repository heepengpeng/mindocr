#include <string>
#include "opencv2/core.hpp"
#include "../../error_code/error_code.h"
namespace MindOCR
{
    class RecCTCLabelDecode
    {
    public:
        RecCTCLabelDecode(){};
        ~RecCTCLabelDecode(){};
        APP_ERROR Init(const std::string character_dict_path);
        APP_ERROR Run(cv::Mat &preds, std::vector<std::string> &texts);
    };

};