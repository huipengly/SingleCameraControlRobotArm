#ifndef __ADS_H_
#define __ADS_H_
#include <Windows.h>		//ads使用需要包含这个文件，不然会未定义null等
#include "TcAdsDef.h"
#include "TcAdsAPI.h"

extern AmsAddr Addr;		//声明AMS地址变量，这里如果不加extern就变成定义，当头文件被二次包含是，就会发生重定义

int Connect();

#endif