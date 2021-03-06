#include "Image.hpp"
#include "ImageReader.hpp"
#include "MattingPerformer.hpp"
#include "ImagePrinter.hpp"

// File path
std::string path_prefix = "..";

std::string img_path = path_prefix + "/bmp/kid/kid.bmp";
std::string img_m_path = path_prefix + "/bmp/kid/kid_m.bmp";

//std::string img_path = path_prefix + "/bmp/peacock/peacock.bmp";
//std::string img_m_path = path_prefix + "/bmp/peacock/peacock_m.bmp";

//std::string img_path = path_prefix + "/bmp/dandelion/dandelion.bmp";
//std::string img_m_path = path_prefix + "/bmp/dandelion/dandelion_m.bmp";

// Global variable
double lambda = 100; // Weight of scribbled piexel obedience
int win_size = 1; // The distance between center and border
double epsilon = 0.00001;
double thresholdForScribble = 0.001;

int main(void)
{
  // Read image
  ImageReader imageReader;
  Image img(imageReader.readImage(img_path));
  Image img_m(imageReader.readImage(img_m_path));
  
  // Perform image matting
  MattingPerformer mattingPerformer(lambda, win_size, epsilon, thresholdForScribble, img.getMatrix(), img_m.getMatrix());
  mattingPerformer.performMatting();
  cv::Mat mattingResultF = mattingPerformer.getMattingResultF();
  cv::Mat mattingResultB = mattingPerformer.getMattingResultB();

  // Print matting result
  Image_Printer imagePrinter;
  imagePrinter.printImage(mattingResultF, "Foreground");
  imagePrinter.printImage(mattingResultB, "Background");

  printf("Result generated\n");
  
  return 0;
}