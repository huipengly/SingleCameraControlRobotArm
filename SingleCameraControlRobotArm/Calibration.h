#ifndef _CALIBRATION_H_
#define _CALIBRATION_H_


#include <opencv2\opencv.hpp>
//#include <cv.h>

using namespace cv;

void init_undistort(Mat &cameraMatrix, Mat &distCoeffs, const Size &imageSize, Mat &map1, Mat &map2);    //ÎÞ»û±ä

#endif