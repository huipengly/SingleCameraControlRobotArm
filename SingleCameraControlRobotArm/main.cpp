#include <iostream>
#include"GetImage.h"
#include"Calibration.h"
#include"kinematics.h"
#include"EyeToHand.h"
#include <windows.h>
#include "C:\TwinCAT\ADSApi\TcAdsDll\Include\TcAdsDef.h" //结构体和常量的声明
#include "C:\TwinCAT\ADSApi\TcAdsDll\Include\TcAdsAPI.h" // ADS函数的声明
#include <string>
using std::string;

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

long nErr, nPort;				//定义端口变量
AmsAddr Addr;			//定义AMS地址变量

struct CartesianCoordinates
{
	double x;
	double y;
	double z;
	double a;		//绕z轴旋转角度
	double b;		//绕y轴
	double c;		//绕x轴
};

int Connect()
{
	nPort = AdsPortOpen();//打开ADS通讯端口
	if (nPort == 0)
	{
		return -1;
	}
	AmsNetId AmsId = { 5, 39, 221, 128, 1, 1 };
	Addr.netId = AmsId;
	Addr.port = 0x8888;

	return 0;
}

int main()
{
	Mat rview, map1, map2;
	Mat cameraMatrix, distCoeffs;
	CartesianCoordinates target_cartesian;

	//double Ajoint[3];
	
	if (!Connect())
	{
		cout << "Connect success!" << endl;
	};

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

//		cv::imwrite("output.bmp", rview);
	
		Point2d center;
		AffInMoment(rview, rightExtrMarks, center);

		cout << "  高  " << center.x << " 宽   " << center.y << endl;

		Mat hand;
		Mat eye = (Mat_<double>(1, 3) << center.x, center.y, 196.97);//定义一个1行3列的矩阵。但是在调试的时候看到的矩阵信息是1*3*1。Mat这个类型显示是?*列*行
		
		EyeToHand(eye, hand);
		
		double add_x = 0, add_y = 0;
		
		if (hand.at<double>(0, 1) > 500)
		{
			add_x = 20;
			add_y = 20;
		}
		//else if (hand.at<double>(0, 0) > 80)
		//{
		//	add_x = 20;
		//	add_y = -20;
		//}

		cout << "\nsend data is " << endl;
		cout << hand.at<double>(0, 0) + add_x << " " <<hand.at<double>(0, 1) + add_y << endl;
		cout << "send?? : ";

		//kinematics_inverse(hand.at<double>(0, 0), hand.at<double>(0, 1), 0, Ajoint);   //x,y,z
		//cout << Ajoint[0] << "," << Ajoint[1] << endl;
		
		////string str;
		////cin >> str;
		char c;
		c = getchar();
		if (c == 'y')
		{
			cout << "send data" << endl;
			target_cartesian.x = hand.at<double>(0, 0) + add_x;
			target_cartesian.y = hand.at<double>(0, 1) + add_y;
			AdsSyncReadWriteReq(&Addr, 0x02, 0x01, 0, NULL, sizeof(CartesianCoordinates), &target_cartesian);
		}

	}
	return 0;
}