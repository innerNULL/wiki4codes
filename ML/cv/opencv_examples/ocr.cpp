
#include <fstream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <tesseract/baseapi.h>

#include "./incubator/cvkit/img_processing/common.h"
#include "./incubator/cvkit/img_processing/ocr/ops.h"
#include "./incubator/cvkit/ocr.h"


int main() {
    //std::string img_path = "../imgs/ocr_0.jpg";
    //std::string img_path = "../imgs/ocr_1.png";
    std::string img_path = "../imgs/ocr_2.png";
    //std::string img_path = "../imgs/willow.jpg";
    //std::string img_path = "../imgs/street_0.jpeg";
    
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

    std::vector<cv::RotatedRect> rotated_boxes = cvkit::contours2bounding_boxes(contours, -90.0, 90.0);
    std::vector< std::vector<cv::Point> > rotated_rec_contours = cvkit::rotated_recs2contours(rotated_boxes);
    cv::Mat img_with_rotated_recs = img;
    cv::drawContours(img_with_rotated_recs, rotated_rec_contours, -1, {255, 0, 0}, 1);
    cv::imshow("ocr", img_with_rotated_recs);
    cv::waitKey();

    std::vector<cv::Mat> cropped_imgs = cvkit::deskew_by_rotated_recs_and_crop_out(
        img, rotated_boxes, -60.0);
    for (cv::Mat& cropped_img : cropped_imgs) {
      //printf("%i, %i\n", 
      //    cropped_img.size().width, cropped_img.size().height);
      //cv::imshow("ocr", cropped_img);
      //cv::waitKey();
    }
    
    cv::imwrite("./tesseract_test.jpg", cropped_imgs[0]);
    tesseract::TessBaseAPI* ocr = cvkit::get_ocr("./tesseract", "chi_sim");
    //tesseract::TessBaseAPI* ocr = cvkit::get_ocr("./tesseract", "eng");
    for (cv::Mat& cropped_img : cropped_imgs) {
      cv::imshow("ocr", cropped_img);
      std::string text = cvkit::identify_text(ocr, cropped_img);
      std::cout << text << std::endl;
      cv::waitKey();
    }

    ocr->End();
    delete ocr;
    return 0;
}
