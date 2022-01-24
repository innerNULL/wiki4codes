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
    const float min_rotation_angle=-360.0, 
    const float max_rotation_angle=360.0, 
    const int32_t min_width=20, const int32_t min_height=20,
    const int32_t max_width=-1, const int32_t max_height=-1, 
    const float rec_proportion_limit=16.0) {
  std::vector<cv::RotatedRect> rotated_boxes;

  for (const auto& contour : contours) {
    auto box = cv::minAreaRect(contour);
    //printf("%f\n", box.angle);
    if (box.size.width < min_width || box.size.height < min_height) {
      continue;
    } else if (max_width > 0 && max_height > 0 
        && box.size.width > max_width && box.size.height > max_height) {
      continue;
    } else if (box.angle < min_rotation_angle) {
      continue;
    } else if (box.angle > max_rotation_angle) {
      continue;
    } else {
      float proportion = (box.angle > -45.0) ? 
          box.size.height / box.size.width : box.size.width / box.size.height;

      if (proportion > rec_proportion_limit) {
        continue;
        //rotated_boxes.push_back(box);
      } else {
        rotated_boxes.push_back(box);
      }
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


cv::Mat rotated_rec_deskew_mat(cv::RotatedRect rotated_rec, 
    double deskew_threshold=-45.0) {
  cv::Mat out;
  double angle = rotated_rec.angle;
  auto size = rotated_rec.size;

  if (angle < deskew_threshold) {
    angle += 90.0;
    std::swap(size.width, size.height);
  }
  cv::Mat transform = cv::getRotationMatrix2D(rotated_rec.center, angle, 1.0);
  return transform;
}


/*
std::vector<cv::Mat> rotated_recs_deskew_mats(
    std::vector<cv::RotatedRect> rotated_recs, 
    double deskew_threshold=-45.0) {
  std::vector<cv::Mat> deskew_mats;
  deskew_mats.resize(rotated_recs.size());
  for (int i = 0; i < rotated_recs.size(); ++i) {
    deskew_mats[i] = rotated_rec_deskew_mat(rotated_recs[i], deskew_threshold);
  }
  return deskew_mats;
}
*/


cv::Mat deskew_img_by_rotated_rec(cv::Mat input_img, 
    cv::RotatedRect rotated_rec, 
    double deskew_threshold=-45.0) {
  cv::Mat deskewed_img;
  cv::Mat deskew_mat = rotated_rec_deskew_mat(
      rotated_rec, deskew_threshold);
  
  cv::warpAffine(input_img, deskewed_img, 
          deskew_mat, input_img.size(), cv::INTER_CUBIC);
  return deskewed_img;
}


cv::Mat deskew_by_rotated_rec_and_crop_out(
    cv::Mat input_img, cv::RotatedRect rotated_rec, 
    double deskew_threshold=-45.0) {
  cv::Mat cropped_img;

  cv::Mat deskewed_img = deskew_img_by_rotated_rec(
          input_img, rotated_rec, deskew_threshold);
  cv::getRectSubPix(deskewed_img, 
          rotated_rec.size, rotated_rec.center, cropped_img);  
  return cropped_img;
}


std::vector<cv::Mat> deskew_by_rotated_recs_and_crop_out(
    cv::Mat input_img, 
    std::vector<cv::RotatedRect> rotated_recs,
    double deskew_threshold=-45.0) {
  std::vector<cv::Mat> cropped_imgs;
  cropped_imgs.resize(rotated_recs.size());

  for (int32_t i = 0; i < rotated_recs.size(); ++i) {
    cropped_imgs[i] = deskew_by_rotated_rec_and_crop_out(
        input_img, rotated_recs[i], deskew_threshold);
    int32_t img_i_width = cropped_imgs[i].size().width;
    int32_t img_i_height = cropped_imgs[i].size().height;
    printf("crop_id: %i, image_width: %i, image_height: %i\n", 
        i, img_i_width, img_i_height);
    if (img_i_width < img_i_height && img_i_width * img_i_height > 1600) {
      cv::rotate(cropped_imgs[i], cropped_imgs[i], cv::ROTATE_90_CLOCKWISE);
      printf("crop_id: %i, re-rotated.\n", i);
    }
    cv::copyMakeBorder(cropped_imgs[i], cropped_imgs[i], 
        10, 10, 10, 10, cv::BORDER_CONSTANT, cv::Scalar(0));
  }
  return cropped_imgs;
}


} // namespace cvkit
