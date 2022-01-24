/// file: ocr.h
/// date: 2021-08-06


#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>


namespace cvkit {


tesseract::TessBaseAPI* get_ocr(
    const std::string dep_file_path, 
    const std::string language) {
  std::string lang_file = language + ".traineddata";
  std::string lang_file_path = dep_file_path + "/" + lang_file;
  std::string url = "https://github.com/tesseract-ocr/tessdata/raw/master/" + lang_file;

  system(("mkdir -p " + dep_file_path).c_str());
  std::ifstream lang_file_f(lang_file_path.c_str());
  if (!std::__fs::filesystem::exists(lang_file_path)) {
    system(("wget " + url + " && mv " + lang_file + " " + dep_file_path).c_str());
  }
  tesseract::TessBaseAPI* ocr = new tesseract::TessBaseAPI();
  //ocr->Init(dep_file_path.c_str(), language.c_str(), tesseract::OEM_TESSERACT_ONLY);
  ocr->Init(dep_file_path.c_str(), language.c_str(), tesseract::OEM_LSTM_ONLY);
  return ocr;
}


std::string identify_text(tesseract::TessBaseAPI* ocr, 
    cv::Mat img, const char* language="eng") {
  //ocr->Init(NULL, language, tesseract::OEM_TESSERACT_ONLY);
  ocr->SetPageSegMode(tesseract::PSM_AUTO);
  //ocr->SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
  ocr->SetImage(img.data, img.cols, img.rows, 3, img.step);

  std::string text = std::string(ocr->GetUTF8Text());
  return text;
}


} // namespace utils
