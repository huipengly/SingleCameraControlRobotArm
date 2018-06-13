#include "EyeToHand.h"

using namespace std;
using namespace cv;

// 像素坐标系到基座坐标系转换矩阵（手眼标定）
Mat A = (   
	     Mat_<double>(3, 3) << 
		 -0.00525197960090061, - 0.134592756370970	,5.64231284225733e-19,
		 0.133499547487584	,0.00113865221315264 ,- 2.19064630029850e-16,
		 - 0.554569845419324,	3.04284393661039	,1.00000000000000
		);

void EyeToHand(Mat &Eye, Mat &Hand)
{
	Hand = Eye*A;
	cout << "A=\n " << A << endl;
	cout << "Eye=\n " << Eye << endl;
	cout << "Hand=\n " << Hand << endl;
}