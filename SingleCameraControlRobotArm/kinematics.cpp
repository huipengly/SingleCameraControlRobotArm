#include "kinematics.h"

double L0 = 0;
double L1 = 314;
double L2 = 367;


/* *************************************************************

*运动学正解（旋转矩阵表达末端姿态）
* pos[]			    末端位置（单位：mm）
* R[]				末端姿态矩阵
* R = R[0]	 R[1]  R[2]
* 	   R[3]	 R[4]  R[5]
* 	   R[6]	 R[7]  R[8]
* r[]				关节转角（单位：°）

***************************************************************/

void kinematics_forward(double* pos, double* r1)
{
	double R[9] = { 0 };
	double r[3] = { 0 };
	for (int i = 0; i<3; i++)
	{
		//角度化为弧度
		r[i] = r1[i] * PI / 180;
	}

	double c1 = cos_(r[0]);		double s1 = sin_(r[0]);
	double c2 = cos_(r[1]);		double s2 = sin_(r[1]);
	double c3 = cos_(r[2]);		double s3 = sin_(r[2]);


	double t14 = L1*c1 - L2*(s1*s2 - c1*c2);
	double t24 = L1*s1 + L2*(c1*s2 + c2*s1);
	double t34 = 0;


	//pos[0] = t14;		//Ax
	//pos[1] = t24;		//Ay
	//pos[2] = t34;		//Aphi

	double t11 = -c3*(s1*s2 - c1*c2) - s3*(c1*s2 + c2*s1);
	double t12 = s3*(s1*s2 - c1*c2) - c3*(c1*s2 + c2*s1);
	double t13 = 0;

	double t21 = c3*(c1*s2 + c2*s1) - s3*(s1*s2 - c1*c2);
	double t22 = -c3*(s1*s2 - c1*c2) - s3*(c1*s2 + c2*s1);
	double t23 = 0;

	double t31 = 0;
	double t32 = 0;
	double t33 = 1;


	R[0] = t11;	R[1] = t12;	R[2] = t13;
	R[3] = t21;	R[4] = t22;	R[5] = t23;
	R[6] = t31;	R[7] = t32;	R[8] = t33;

	
    //	防止浮点数计算误差
	if (fabs_(R[0] - 1) < 1e-6)
	{
		R[0] = 1;
	}
	else if (fabs_(R[0] - (-1)) < 1e-6)
	{
		R[0] = -1;
	}

	pos[0] = t14;							//Ax
	pos[1] = t24;							//Ay
	pos[2] = acos_(R[0]) * 180 / PI;		//Aphi
}

/* *************************************************************

* 运动学反解
* phi                连杆3在平面内的方位角（相对于基坐标系x轴正方向）
*
* x 、y			    末端位置（单位：mm）

2018-01-23 暴力解决倍福的sqrt_不能输入负数bug，等待修复。修复失败
***************************************************************/

void kinematics_inverse(double x, double y, double phi, double* Ajoint)    //求逆解角度
{

	phi = phi/180.0*PI;

	double r1, r2, r3;
	double joint[6];

	/*
	joint[0]-ioint[2]为解1
	joint[3]-ioint[5]为解2
	*/

	double actualAngle[3] = { 0 };	    // actual angle


	// solution 1
	double c2 = (pow_(x, 2) + pow_(y, 2) - pow_(L1, 2) - pow_(L2, 2)) / (2 * L1*L2);

	//	防止浮点数计算误差
	if (fabs_(c2 - 1) < 1e-1)
	{
		c2 = 1;
	}
	double s2 = sqrt_(1 - pow_(c2, 2));


	r2 = atan2_(s2, c2);

	double k1 = L1 + L2 * c2;
	double k2 = L2*s2;

	r1 = atan2_(y, x) - atan2_(k2, k1);

	r3 = phi - r2 - r1;

	joint[0] = r1/PI*180.0;
	joint[1] = r2/PI*180.0;
	joint[2] = r3/PI*180.0;


	// solution 2
	s2 = -s2;
	r2 = atan2_(s2, c2);


	k1 = L1 + L2 * c2;
	k2 = L2*s2;

	r1 = atan2_(y, x) - atan2_(k2, k1);

	r3 = phi - r2 - r1;

	joint[3] = r1/PI*180.0;
	joint[4] = r2/PI*180.0;
	joint[5] = r3/PI*180.0;


	// standard

	double AngleDSum[2];

	AngleDSum[0] = fabs_(joint[0] - actualAngle[0]) + fabs_(joint[1] - actualAngle[1]) + fabs_(joint[2] - actualAngle[2]);	// sum of angle displacement

	AngleDSum[1] = fabs_(joint[3] - actualAngle[0]) + fabs_(joint[4] - actualAngle[1]) + fabs_(joint[5] - actualAngle[2]);	// sum of angle displacement


	if (AngleDSum[0] < AngleDSum[1])
	{
		for (int i = 0; i < 3; i++)
		{
			Ajoint[i] = joint[i];
		}
		//return joint;

	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			Ajoint[i] = joint[i + 3];
		}
		//return joint + 3;
	}

}
