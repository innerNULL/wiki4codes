/// file: ops.h
/// date: 2021-08-07


#include <vector>
#include <opencv2/opencv.hpp>


namespace cvkit {


cv::Mat morphological_dilation(cv::Mat input_img) {
  auto kernel = cv::getStructuringElement(
      cv::MORPH_CROSS, cv::Size(3,3));
  cv::Mat dilated_img;
  cv::dilate(input_img, dilated_img, kernel, cv::Point(-1, -1), 5);
  return dilated_img;
}


std::vector< std::vector<cv::Point> > get_ocr_contours(
    cv::Mat processed_img) {
  std::vector< std::vector<cv::Point> > ocr_contours;
  cv::findContours(processed_img, 
      ocr_contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
  return ocr_contours;
}


std::vector<cv::RotatedRect> contours2bounding_boxes(
    std::vector< std::vector<cv::Point> > contours, 
    const int32_t min_width=20, const int32_t min_height=20, 
    const float rec_proportion_limit=2.0) {
  std::vector<cv::RotatedRect> rotated_boxes;

  for (const auto& contour : contours) {
    auto box = cv::minAreaRect(contour);
    if (box.size.width < min_width || box.size.height < min_height) {
      continue;
    } else {
      /*
      float proportion = (box.angle > -45.0) ? 
          box.size.height / box.size.width : box.size.width / box.size.height;

      if (proportion > rec_proportion_limit) {
        continue;
      } else {
        rotated_boxes.push_back(box);
      }
      */
      rotated_boxes.push_back(box);
    }
  }
  return rotated_boxes;
}


std::vector< std::vector<cv::Point> > rotated_recs2contours(
    std::vector<cv::RotatedRect> rotated_recs) {
  std::vector< std::vector<cv::Point> > contours;
  for (const cv::RotatedRect& rotated_rec : rotated_recs) {
    std::vector<cv::Point> vertices;
    vertices.resize(4);

    cv::Point2f vertices2f[4];
    rotated_rec.points(vertices2f);
    for(int i = 0; i < 4; ++i) { vertices[i] = vertices2f[i]; }
    contours.emplace_back(vertices);
  }
  return contours;
}


void visualize_contour(cv::Mat img, 
    std::vector< std::vector<cv::Point> > contours) {
  return;
}


} // namespace cvkit
