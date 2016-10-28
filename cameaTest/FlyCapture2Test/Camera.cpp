#include "Camera.h"
#include "stdafx.h"
#include <iostream>
#include <sstream>
#include "FlyCapture2.h"

using namespace FlyCapture2;
using namespace std;

void PrintBuildInfo()
{
	FC2Version fc2Version;
	Utilities::GetLibraryVersion(&fc2Version);

	ostringstream version;
	version << "FlyCapture2 library version: " << fc2Version.major << "." << fc2Version.minor << "." << fc2Version.type << "." << fc2Version.build;
	cout << version.str() << endl;

	ostringstream timeStamp;
	timeStamp << "Application build date: " << __DATE__ << " " << __TIME__;
	cout << timeStamp.str() << endl << endl;
}

void PrintCameraInfo(CameraInfo* pCamInfo)
{
	cout << endl;
	cout << "*** CAMERA INFORMATION ***" << endl;
	cout << "Serial number -" << pCamInfo->serialNumber << endl;
	cout << "Camera model - " << pCamInfo->modelName << endl;
	cout << "Camera vendor - " << pCamInfo->vendorName << endl;
	cout << "Sensor - " << pCamInfo->sensorInfo << endl;
	cout << "Resolution - " << pCamInfo->sensorResolution << endl;
	cout << "Firmware version - " << pCamInfo->firmwareVersion << endl;
	cout << "Firmware build time - " << pCamInfo->firmwareBuildTime << endl << endl;

}

void PrintError(Error error)
{
	error.PrintErrorTrace();
}

Camera* SetSingleCamera(PGRGuid guid)
{
	Error error;
	Camera* cam = new Camera;

	// Connect to a camera
	error = cam->Connect(&guid);
	if (error != PGRERROR_OK)
	{
		PrintError(error);
		exit(-1);
	}

	// Get the camera information
	CameraInfo camInfo;
	error = cam->GetCameraInfo(&camInfo);
	if (error != PGRERROR_OK)
	{
		PrintError(error);
		exit(-1);
	}
	PrintCameraInfo(&camInfo);
	// Get the camera configuration
	FC2Config config;
	error = cam->GetConfiguration(&config);
	if (error != PGRERROR_OK)
	{
		PrintError(error);
		exit(-1);
	}

	// Set the number of driver buffers used to 10.
	config.numBuffers = 10;

	// Set the camera configuration
	error = cam->SetConfiguration(&config);
	if (error != PGRERROR_OK)
	{
		PrintError(error);
		exit(-1);
	}
	return cam;
}

int capture(Camera* cam, int id, string& fileName) {
	Image rawImage;
	Error error;
	CameraInfo camInfo;
	cam->GetCameraInfo(&camInfo);
	// Retrieve an image
	error = cam -> RetrieveBuffer(&rawImage);
	if (error != PGRERROR_OK)
	{
		PrintError(error);
		return -1;
	}

	cout << "Grabbed image " << id << endl;

	// Create a converted image
	Image convertedImage;

	// Convert the raw image
	error = rawImage.Convert(PIXEL_FORMAT_MONO8, &convertedImage);
	if (error != PGRERROR_OK)
	{
		PrintError(error);
		return -1;
	}

	// Create a unique filename

	ostringstream picName;
	picName << "FlyCapture2Test-" << camInfo.serialNumber << "-" << id << ".jpeg";
	fileName = picName.str();
	// Save the image. If a file format is not passed in, then the file
	// extension is parsed to attempt to determine the file format.
	error = convertedImage.Save(picName.str().c_str());
	if (error != PGRERROR_OK)
	{
		PrintError(error);
		return -1;
	}
}

int StartCamera(Camera* cam) {
	Error error;
	error = cam->StartCapture();
	if (error != PGRERROR_OK)
	{
		PrintError(error);
		return -1;
	}
}

int StopAndDisconnectCamera(Camera* cam) {
	Error error;
	// Stop capturing images
	error = cam->StopCapture();
	if (error != PGRERROR_OK)
	{
		PrintError(error);
		return -1;
	}

	// Disconnect the camera
	error = cam->Disconnect();
	if (error != PGRERROR_OK)
	{
		PrintError(error);
		return -1;
	}
}
