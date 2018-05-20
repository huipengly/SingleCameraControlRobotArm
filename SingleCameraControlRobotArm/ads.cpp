#include "ads.h"

AmsAddr   Addr;			//定义AMS地址变量

int Connect()
{
	long nPort = AdsPortOpen();//打开ADS通讯端口
	if (nPort == 0)
	{
		return -1;
	}
	AmsNetId AmsId = { 5, 39, 221, 128, 1, 1 };
	Addr.netId = AmsId;
	Addr.port = 0x8888;

	return 0;
}