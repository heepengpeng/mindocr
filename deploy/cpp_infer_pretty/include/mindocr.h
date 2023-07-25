#pragma once

#include <include/ocr_cls.h>
#include <include/ocr_det.h>
#include <include/ocr_rec.h>


namespace mindspore_infer {

    class  MindOCR {
    public:
        explicit MindOCR();

        ~MindOCR();

        std::vector<std::vector<OCRPredictResult>> ocr(std::vector<cv::Mat> img_list,
                                                       bool det = true,
                                                       bool rec = true,
                                                       bool cls = true);

        std::vector<OCRPredictResult> ocr(cv::Mat img, bool det = true,
                                          bool rec = true, bool cls = true);

        void reset_timer();

    protected:
        std::vector<double> time_info_det = {0, 0, 0};
        std::vector<double> time_info_rec = {0, 0, 0};
        std::vector<double> time_info_cls = {0, 0, 0};

        void det(cv::Mat img, std::vector<OCRPredictResult> &ocr_results);

        void rec(std::vector<cv::Mat> img_list,
                 std::vector<OCRPredictResult> &ocr_results);

        void cls(std::vector<cv::Mat> img_list,
                 std::vector<OCRPredictResult> &ocr_results);

    private:
        DBDetector *detector_ = nullptr;
        Classifier *classifier_ = nullptr;
        CRNNRecognizer *recognizer_ = nullptr;
    };

} // namespace PaddleOCR
