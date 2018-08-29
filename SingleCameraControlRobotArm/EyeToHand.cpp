#include "EyeToHand.h"

using namespace std;
using namespace cv;

// 像素坐标系到基座坐标系转换矩阵（手眼标定）
Mat A = (
			Mat_<double>(3, 3) <<
	-0.00175037189971019, -0.133631176260602,	2.62006183644348e-16,
	0.126085313968551,	0.00180448020567125, - 2.26668964566183e-17,
	- 0.442857942560711,	3.32943308764783,	1.00000000000000
		);

void EyeToHand(Mat &Eye, Mat &Hand)
{
	Hand = Eye*A;
	cout << "A=\n " << A << endl;
	cout << "Eye=\n " << Eye << endl;
	cout << "Hand=\n " << Hand << endl;
}