#include "EyeToHand.h"

using namespace std;
using namespace cv;

// 像素坐标系到基座坐标系转换矩阵（手眼标定）
Mat A = (
			Mat_<double>(3, 3) <<
			0.00161611272389343, -0.144543184417082, -1.89693268317570e-16,
			0.137532049384641, 0.00650909188141906, -6.03094736800737e-17,
			-0.815835069894144, 3.74315885960142, 1.00000000000001
		);

void EyeToHand(Mat &Eye, Mat &Hand)
{
	Hand = Eye*A;
	cout << "A=\n " << A << endl;
	cout << "Eye=\n " << Eye << endl;
	cout << "Hand=\n " << Hand << endl;
}