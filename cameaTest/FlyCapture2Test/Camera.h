#pragma once
#include "stdafx.h"
#include <iostream>
#include <sstream>
#include "FlyCapture2.h"

using namespace FlyCapture2;
using namespace std;

void PrintBuildInfo();
void PrintCameraInfo(CameraInfo* pCamInfo);
void PrintError(Error error);
Camera* SetSingleCamera(PGRGuid guid);
int capture(Camera* cam, int id, string& str);
int StartCamera(Camera* cam);
int StopAndDisconnectCamera(Camera* cam);

