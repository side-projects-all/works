#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[]) {
  std::cout << "hi world\n";
  /*
  cv::Mat image;
  image = cv::imread("C:/Users/pj/Desktop/for_lot/lot_2024.png");

  if (!image.data) {
    std::cout << "no image data\n";
    return -1;
  }

  std::string name = "Display image";
  */

  cv::Mat image(600, 800, CV_8UC1, cv::Scalar(100, 250, 30));
  std::string name = "blank image";
  cv::namedWindow(name, cv::WINDOW_AUTOSIZE);
  cv::imshow(name, image);
  cv::waitKey(0);
  cv::destroyWindow(name);
  
  
  return 0;
}