#include <iostream>
#include"GetImage.h"
#include"Calibration.h"
#include"kinematics.h"
#include"EyeToHand.h"


/*
  经典经验：
  1、检查语句错误，将断点放置在本句。（检查内存溢出、程序崩溃的错误）
  2、检查语句运行结果，将断点放置在本句的下一句。（逻辑错误）
*/
using namespace cv;
using namespace std;

int main()
{
	Mat rview, map1, map2;
	Mat cameraMatrix, distCoeffs;

	double Ajoint[3];


	//EyeToHand(rview, rview);
	//getchar();
	//return 0;
	
	InitGetImages();

	while (1)
	{
		static DShowLib::Grabber::tMemBufferPtr pLeft;
		static DShowLib::Grabber::tMemBufferPtr pRight;
		Mat leftGray, rightGray;
		vector<Point2d> leftExtrMarks;
		vector<Point2d> rightExtrMarks;
		//矫正之前
		GetImage(pRight,rightGray);
		//AffInMoment(rightGray, rightExtrMarks);
        //矫正之后
		init_undistort(cameraMatrix, distCoeffs, rightGray.size(), map1, map2);

		remap(rightGray, rview, map1, map2, INTER_LINEAR);	//矫正之后图片尺寸和原图一样

		cv::imwrite("output.bmp", rview);
	
		Point2d center;
		AffInMoment(rview, rightExtrMarks, center);

		cout << "  高  " << center.x << " 宽   " << center.y << endl;

		Mat hand;
		Mat eye = (Mat_<double>(1, 3) << center.x, center.y, 282.1969697);//定义一个1行3列的矩阵。但是在调试的时候看到的矩阵信息是1*3*1。Mat这个类型显示是?*列*行
		
		EyeToHand(eye, hand);

		kinematics_inverse(hand.at<double>(0, 0), hand.at<double>(0, 1), 0, Ajoint);   //x,y,z
		cout << Ajoint[0] << "," << Ajoint[1] << endl;

	}
	return 0;
}