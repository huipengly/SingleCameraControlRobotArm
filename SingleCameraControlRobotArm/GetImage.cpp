#include <boost/timer.hpp>
#include <opencv2/opencv.hpp> 
//#include <highgui.h>
#include "GetImage.h"

using namespace cv;
using namespace std;

/*
*  为从相机获取图像做好准备
*  调用该函数后，可以使用GetImage获取图像
*/
void InitGetImages()
{
	OpenCamera();
	StartCamera();
	Sleep(500);
}

/*
*  不需要调用图像之后，调用该函数，可以关闭相机
*/
void EndGetImages()
{
	CloseCamera();
}


/*
*   图像采集及图像预处理
*/
bool GetImage( DShowLib::Grabber::tMemBufferPtr &pRight, Mat& rightGray)  //左右图像的搜索信息
{

	if (!GetImageBuffer(&pRight))
	{
		printf("error in file:GetImageFromCamera.cpp  function:InitOpenCVmats\n");
		return false;
	}

	Size size(pRight->getBitmapInfoHeader()->biWidth, pRight->getBitmapInfoHeader()->biHeight);


	/*
	//【1】CV_8UC1---则可以创建----8位无符号的单通道---灰度图片------grayImg
           #define CV_8UC1 CV_MAKETYPE(CV_8U,1)
           #define CV_8UC2 CV_MAKETYPE(CV_8U,2)
	//【2】CV_8UC3---则可以创建----8位无符号的三通道---RGB彩色图像---colorImg 
           #define CV_8UC3 CV_MAKETYPE(CV_8U,3)
	//【3】CV_8UC4--则可以创建-----8位无符号的四通道---带透明色的RGB图像 
           #define CV_8UC4 CV_MAKETYPE(CV_8U,4)
    */
      
	Mat rightRGB = Mat(size, CV_8UC3);

	rightRGB.data = (uchar*)(pRight->getPtr());

    //  //调整图像大小
	//Size ResImgSiz = Size(1280*0.5, 960*0.5);
	//resize(rightRGB, rightRGB, ResImgSiz, CV_INTER_CUBIC);

	//imshow("right", rightRGB);
	//waitKey(0);
	
	cvtColor(rightRGB, rightGray, CV_RGB2GRAY);
	
	//调整图像大小
	//Size ResImgSiz = Size(1280*0.8, 960*0.8);
	//resize(rightGray, rightGray, ResImgSiz, CV_INTER_CUBIC);
	
	
	GaussianBlur(rightGray, rightGray, Size(25, 25), 0, 0);	//高斯滤波
   
	threshold(rightGray, rightGray, 40, 255, THRESH_BINARY); //二值化

	Canny(rightGray, rightGray, 80, 40, 3);		//canny边缘 二值化
	
	//imshow("left", leftGray);

	Mat rightsize;
	Size ResImgSiz = Size(1280*0.8, 960*0.8);
	resize(rightGray, rightsize, ResImgSiz, CV_INTER_CUBIC);
	imshow("right", rightsize);
	waitKey(0);
	
	return true;

}

/*
*   基于轮廓的仿射不变矩特征提取,提取标志球的圆心像素坐标
*/

void AffInMoment(Mat & image, vector<Point2d> & extrMarks, Point2d & center)
{
	vector< vector<Point> >contours; 
	vector<Vec4i>hierarchy;     //模板
	CvBox2D box;
	unsigned int i;
	
	/*
	* Opencv中通过使用findContours函数，简单几个步骤就可以检测出物体的轮廓，很方便。
	
	* 第一个参数：image，单通道图像矩阵，可以是灰度图，但更常用的是二值图像，一般是经过Canny、拉普拉斯等边缘检测算子处理过的二值图像；
	
	* 第二个参数：contours，定义为“vector<vector<Point>> contours”，是一个向量，并且是一个双重向量，向量内每个元素保存了一组由连续的Point点构成的点的集合的向量，
	              每一组Point点集就是一个轮廓。有多少轮廓，向量contours就有多少元素。
    
	* 第三个参数：hierarchy，定义为“vector<Vec4i> hierarchy”，先来看一下Vec4i的定义：
                  typedef    Vec<int, 4>   Vec4i;                                                                                                                                       
                  Vec4i是Vec<int,4>的别名，定义了一个“向量内每一个元素包含了4个int型变量”的向量。
                  所以从定义上看，hierarchy也是一个向量，向量内每个元素保存了一个包含4个int整型的数组。
                  向量hiararchy内的元素和轮廓向量contours内的元素是一一对应的，向量的容量相同。
                  hierarchy向量内每一个元素的4个int型变量——hierarchy[i][0] ~hierarchy[i][3]，
				  分别表示第i个轮廓的后一个轮廓、前一个轮廓、父轮廓、内嵌轮廓的索引编号。
				  如果当前轮廓没有对应的后一个轮廓、前一个轮廓、父轮廓或内嵌轮廓的话，则hierarchy[i][0] ~hierarchy[i][3]的相应位被设置为默认值-1。
	
	*第四个参数： int型的mode，定义轮廓的检索模式：
                  取值一：CV_RETR_EXTERNAL 只检测最外围轮廓，包含在外围轮廓内的内围轮廓被忽略
                  
				  取值二：CV_RETR_LIST     检测所有的轮廓，包括内围、外围轮廓，但是检测到的轮廓不建立等级关系，彼此之间独立，没有等级关系，
				                           这就意味着这个检索模式下不存在父轮廓或内嵌轮廓，所以hierarchy向量内所有元素的第3、第4个分量都会被置为-1，具体下文会讲到
                  
				  取值三：CV_RETR_CCOMP    检测所有的轮廓，但所有轮廓只建立两个等级关系，外围为顶层，若外围内的内围轮廓还包含了其他的轮廓信息，则内围内的所有轮廓均归属于顶层

                  取值四：CV_RETR_TREE，   检测所有的轮廓，所有轮廓建立一个等级树结构。外层轮廓包含内层轮廓，内层轮廓还可以继续包含内嵌轮廓。
	*第五个参数： int型的method，定义轮廓的近似方法：
                  取值一：CV_CHAIN_APPROX_NONE   保存物体边界上所有连续的轮廓点到contours向量内
                  取值二：CV_CHAIN_APPROX_SIMPLE 仅保存轮廓的拐点信息，把所有轮廓拐点处的点保存入contours向量内，拐点与拐点之间直线段上的信息点不予保留
                  取值三和四：CV_CHAIN_APPROX_TC89_L1，CV_CHAIN_APPROX_TC89_KCOS使用teh-Chinl chain 近似算法

    *第六个参数： Point偏移量，所有的轮廓信息相对于原始图像对应点的偏移量，相当于在每一个检测出的轮廓点上加上该偏移量，并且Point还可以是负值！
	*/

	findContours(image, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);  
	for (i = 0; i < contours.size(); i++)           //contours.size()表示轮廓数
	{
		Moments moment;
		moment = moments(contours[i], false);       //基于轮廓的不变距
		double u00 = moment.m00; double u01 = moment.m01; double u10 = moment.m10;
		double u20 = moment.mu20; double u11 = moment.mu11; double u02 = moment.mu02;
		double u30 = moment.mu30; double u21 = moment.mu21; double u12 = moment.mu12; double u03 = moment.mu03;  //原点距和中心距
		
		double I1 = (u02*u20 - u11*u11) / pow(u00, 4);		//一阶矩
		double I2 = (u30*u30*u03*u03 - 6 * u30*u12*u21*u03 + 4 * u30*pow(u12, 3) + 4 * u03*pow(u21, 3) - 3 * u21*u21*u12*u12) / pow(u00, 10);
		double I3 = (u20*(u21*u03 - u12*u12) - u11*(u30*u03 - u21*u12) + u02*(u30*u12 - u21*u21)) / pow(u00, 7);
		
		double Ia = abs(I1 - 0.006332) - 0.0003;   //不变矩阈值判断 与标准不变矩值比较
		double Ib = abs(I2) - 0.00001;
		double Ic = abs(I3) - 0.00001;

		if (Ia <= 0 && Ib<0 && Ic<0)
		{
			box = fitEllipse(contours[i]);	//椭圆曲线拟合
			if (box.size.width>10 && box.size.height>10)
			{
				//Point2d center;
				center.x = int(box.center.x);		//图像缩放（取整）
				center.y = int(box.center.y);
				//cout << "  高  " << center.x << " 宽   " << center.y << endl;
				cout << "Find the center." << endl; //判断是否找圆心
				extrMarks.push_back(center);
				ellipse(image, box, Scalar(0, 250, 0), 0.2);	//画出椭圆
				circle(image, box.center, 1, Scalar(250, 0, 0), 0.01, 8);	//画出椭圆心
			}
		}
	}

}
