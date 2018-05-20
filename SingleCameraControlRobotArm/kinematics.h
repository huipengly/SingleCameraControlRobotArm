#ifndef _KINEMATICS_H_
#define _KINEMATICS_H_


//#include <Fpu87.h>

#ifndef PI
#define PI 3.14159265358979
#endif

#include "math.h"
#define sin_ sin
#define cos_ cos
#define acos_ acos
#define pow_ pow
#define sqrt_ sqrt
#define atan2_ atan2
#define fabs_ fabs


/************************************************
* 运动学参数
* R[3][3]				3×3旋转矩阵
* X[3]					笛卡尔空间xyz位置(单位：mm)
* joint[3]				关节角度（单位：°）
* kps[3]				等效转轴3分量×转角
* Kine_Forward			运动学正解（已知joint[3] -> 求解X[3]、R[3][3]）
* Kine_Inverse			运动学反解（已知X[3]、R[3][3] -> 求解joint[3]）
* **********************************************/


void kinematics_forward(double* pos, double* r);
void kinematics_inverse(double x, double y, double phi, double* Ajoint);


#endif         /* KINEMATICS_H_ */