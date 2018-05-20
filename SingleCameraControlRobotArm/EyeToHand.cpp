#include "EyeToHand.h"
using namespace std;

using namespace cv;

// 像素坐标系到基座坐标系转换矩阵
Mat A = (Mat_<double>(3, 3) << -0.232798599, -0.014661695, 1.47E-14, 0.011549461, -0.239178083, 1.72E-14, 2.900046679, 2.202405533, 1);

void EyeToHand(Mat &Eye, Mat &Hand)
{
	Hand = Eye*A;
	cout << "A=\n " << A << endl;
	cout << "Eye=\n " << Eye << endl;
	cout << "Hand=\n " << Hand << endl;
}