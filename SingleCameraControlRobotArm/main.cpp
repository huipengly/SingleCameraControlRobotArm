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

/*
 （小师弟代码修改）
  1、运动学程序改正
  2、关节空间PTP：三次多项式、double s
  3、笛卡尔空间：直线、圆弧（double s)
  4、认真向小师弟学习利用GitHub，学会使用git
  5、加上TCP（工具坐标系）
*/
using namespace cv;
using namespace std;

int main()
{
	Mat rview, map1, map2;
	Mat cameraMatrix, distCoeffs;

	double Ajoint[3];
	
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
		Mat eye = (Mat_<double>(1, 3) << center.x, center.y, 196.97);//定义一个1行3列的矩阵。但是在调试的时候看到的矩阵信息是1*3*1。Mat这个类型显示是?*列*行
		
		EyeToHand(eye, hand);
		
		cout << hand.at<double>(0, 0) << " " <<hand.at<double>(0, 1) << endl;

		//kinematics_inverse(hand.at<double>(0, 0), hand.at<double>(0, 1), 0, Ajoint);   //x,y,z
		//cout << Ajoint[0] << "," << Ajoint[1] << endl;

	}
	return 0;
}