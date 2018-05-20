
#include"Camera.h"

std::shared_ptr<Grabber>grabber = std::make_shared<Grabber>();

static smart_ptr<FrameHandlerSink> pSink;


//从文件中打开摄像机，设定摄像机的参数
bool openDeviceFromFile(_DSHOWLIB_NAMESPACE::Grabber& gr, const std::string& devStateFilename)
{
	if (gr.loadDeviceStateFromFile(devStateFilename))
	{
		std::cout << "Device opened from: <" << devStateFilename << ">." << std::endl;
	}
	else
	{
		std::cout << "File <" << devStateFilename << "> either not found, or device could not be opened from it." << std::endl;
	}
	if (!gr.showDevicePage() || !gr.isDevValid())
	{
		return false;
	}
	gr.saveDeviceStateToFile(devStateFilename, true, true, false);
	gr.setOverlayBitmapPathPosition(ePP_NONE);
	return true;
}


bool OpenCamera()
{
	//初始化库
	DShowLib::InitLibrary();

	if (!openDeviceFromFile(*grabber, "lastSelectedDeviceState2.xml"))//从文件里打开摄像机
	{
		printf("Init right camera failed!");
		printf("Error: %s\n", grabber->getLastError().c_str());
		return false;
	}

	//set Grabber sinktype
	pSink = FrameHandlerSink::create(eRGB24, 10);
	pSink->setSnapMode(true);
	grabber->setSinkType(pSink);


	if (!grabber->prepareLive(false))
	{
		printf("Error: %s\n", grabber->getLastError().c_str());
		return false;
	}

	return true;

}


bool GetImageBuffer(MemBufferCollection::tMemBufferPtr * buffer)
{
	Error err = pSink->snapImages(1);
	if (err.isError())
	{
		printf("%s\n", err.c_str());
		return false;
	}

	*buffer = pSink->getLastAcqMemBuffer();  //复制内存

	return true;
}


bool StartCamera()  //开启Live模式
{
	if (grabber->startLive(false))
	{

		return true;
	}
	printf("Error in file:Camera.cpp, function:StartCamera, start camera failed!\n");
	return false;
}

void SuspendCamera()//挂起相机
{
	grabber->suspendLive();

}

void CloseCamera()//关闭相机
{
	if (grabber != NULL)
	{
		grabber->stopLive();
		grabber->closeDev();
	}

}