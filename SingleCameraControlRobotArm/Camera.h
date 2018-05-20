#pragma once                     //保证头文件被编译一次
#pragma warning (disable:4996)   //将4996警报置为失效

#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <memory>
#include "tisudshl.h"

using namespace _DSHOWLIB_NAMESPACE;

bool OpenCamera();
bool StartCamera();
void SuspendCamera();
void CloseCamera();


bool GetImageBuffer(MemBufferCollection::tMemBufferPtr *buffer);

bool openDeviceFromFile(_DSHOWLIB_NAMESPACE::Grabber& gr, const std::string& devStateFilename);