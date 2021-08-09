/// file: img_processing.h
/// date: 2021-08-06


#include <vector>
#include <opencv2/opencv.hpp>


namespace cvkit {


cv::Mat binarize(cv::Mat input) {
  cv::Mat binaryImage;
  cv::cvtColor(input, input,  cv::COLOR_BGR2GRAY);
  cv::threshold(input,  binaryImage,  0,  255,  cv::THRESH_OTSU);

  int white = cv::countNonZero(binaryImage);
  int black = binaryImage.size().area() - white;

  return white > black ? ~binaryImage : binaryImage;
}


} // namespace utils
