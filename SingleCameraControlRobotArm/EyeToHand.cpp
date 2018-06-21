#include "EyeToHand.h"

using namespace std;
using namespace cv;

// 像素坐标系到基座坐标系转换矩阵（手眼标定）
Mat A = (
			Mat_<double>(3, 3) <<
			0.00331200323778345, -0.148241597540430, -3.30155801141389e-16,
			0.141405588223739, 0.00170285193125988, -1.15809861809056e-16,
			-0.469236555129719,4.06317728853934,1.00000000000001
		);

void EyeToHand(Mat &Eye, Mat &Hand)
{
	Hand = Eye*A;
	cout << "A=\n " << A << endl;
	cout << "Eye=\n " << Eye << endl;
	cout << "Hand=\n " << Hand << endl;
}