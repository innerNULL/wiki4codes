
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

#include "./incubator/cvkit/img_processing/common.h"
#include "./incubator/cvkit/img_processing/ocr/ops.h"



int main() {
    //std::string img_path = "../imgs/ocr_0.jpg";
    std::string img_path = "../imgs/ocr_1.png";
    //std::string img_path = "../imgs/willow.jpg";
    cv::namedWindow( "ocr", cv::WINDOW_NORMAL);
    cv::resizeWindow("ocr", 800, 600);

    cv::getBuildInformation();
    cv::Mat img = cv::imread(cv::samples::findFile(img_path), cv::IMREAD_COLOR);
    cv::imshow("ocr", img);
    cv::waitKey();

    cv::Mat bin_img = cvkit::binarize(img);
    cv::imshow("ocr", bin_img);  
    cv::waitKey(); 

    cv::Mat dilated_img = cvkit::morphological_dilation(bin_img);
    cv::imshow("ocr", dilated_img);
    cv::waitKey();

    std::vector< std::vector<cv::Point> > contours = cvkit::get_ocr_contours(dilated_img);
    cv::Mat img_with_contours = img;
    //cv::drawContours(img_with_contours, contours, -1, {255, 0, 0}, 1);
    //cv::imshow("ocr", img_with_contours);
    //cv::waitKey();

    std::vector<cv::RotatedRect> rotated_boxes = cvkit::contours2bounding_boxes(contours);
    std::vector< std::vector<cv::Point> > rotated_rec_contours = cvkit::rotated_recs2contours(rotated_boxes);
    cv::Mat img_with_rotated_recs = img;
    cv::drawContours(img_with_rotated_recs, rotated_rec_contours, -1, {255, 0, 0}, 1);
    cv::imshow("ocr", img_with_rotated_recs);
    cv::waitKey();
    return 0;
}
