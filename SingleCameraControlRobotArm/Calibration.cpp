#include"Calibration.h"
using namespace std;

//初始化镜头矫正参数
//需要输入相机内参、畸变系数、照片尺寸、两个map（不知道干嘛用的）
void init_undistort(Mat &cameraMatrix, Mat &distCoeffs, const Size &imageSize, Mat &map1, Mat &map2)
{
	cameraMatrix = Mat::eye(3, 3, CV_64F);
	cameraMatrix.at<double>(0, 0) = 4.3391778255203135e+003;
	cameraMatrix.at<double>(0, 1) = 0.;
	cameraMatrix.at<double>(0, 2) = 1.2761969108831729e+003;
	cameraMatrix.at<double>(1, 1) = 4.3278041842134598e+003;
	cameraMatrix.at<double>(1, 2) = 7.0848935421128635e+002;

	distCoeffs = Mat::zeros(5, 1, CV_64F);
	distCoeffs.at<double>(0, 0) = -1.1829131587990460e-001;
	distCoeffs.at<double>(1, 0) = 5.6532168750708756e-001;
	distCoeffs.at<double>(2, 0) = 3.4379475924984858e-003;
	distCoeffs.at<double>(3, 0) = 9.8004771755982791e-004;
	distCoeffs.at<double>(4, 0) = -1.1442673176140812e+000;

	//函数具体介绍
	//https://docs.opencv.org/2.4/modules/imgproc/doc/geometric_transformations.html#initundistortrectifymap
	initUndistortRectifyMap(cameraMatrix, distCoeffs, Mat(),
		getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, imageSize, 1, imageSize, 0),
		imageSize, CV_16SC2, map1, map2);
}