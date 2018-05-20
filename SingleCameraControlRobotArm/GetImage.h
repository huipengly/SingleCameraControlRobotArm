/*
* 获取相机图像，并转换为opencv格式
* 根据相机图片格式，初始化opencv图像类格式
* 2018.4.9
* Author：LEO
*/

#pragma warning( disable : 4996)
#ifndef _GETIMAGE_H_
#define _GETIMAGE_H_

#include <opencv2\opencv.hpp>
//#include <cv.h>
#include <Windows.h>
#include <iostream>
#include <vector>
#include "Camera.h"

using namespace cv;

/*
*  获取图像
*/

//   图像采集及图像预处理
bool GetImage(DShowLib::Grabber::tMemBufferPtr &pRight, Mat& rightGray);   //左右图像的搜索信息

//   基于轮廓的仿射不变矩特征提取,提取标志球的圆心像素坐标
void AffInMoment(Mat & image, vector<Point2d> & extrMarks, Point2d &center);

/*
* 为从相机获取图像做好准备
* 调用该函数后，可以使用GetImage获取图像
*/
void InitGetImages();

/*
* 不需要调用图像之后，调用该函数，可以关闭相机
*
*/
void EndGetImages();


#endif

