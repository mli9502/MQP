// SerialPort.cpp : main project file.

#include "stdafx.h"
#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include "Serial.h"
#include <string>
#include <thread>
#include <fstream>
#include "Camera.h"
#include <vector>
#include <chrono>
#include <ctime>

#define CAMERA 0
#define OBD 1
#define SLEEP_TIME 100

using namespace std;
using namespace FlyCapture2;

volatile long id = 0;
volatile int cameraFlg = 1;

string cameraFile = "camera.txt";
string obdFile = "obd.txt";

void control(int);
void cameraFunc();
void dataFunc();

void control(int tag) {
	if (tag == CAMERA) {
		cameraFunc();
	}
	else {
		dataFunc();
	}
}

void cameraFunc() {
	Error error;
	BusManager busMgr;
	unsigned int numCameras;
	error = busMgr.GetNumOfCameras(&numCameras);
	if (error != PGRERROR_OK)
	{
		PrintError(error);
		return;
	}
	PGRGuid guid;
	vector<Camera*> cams;
	for (unsigned int i = 0; i < numCameras; i++)
	{
		error = busMgr.GetCameraFromIndex(i, &guid);
		cams.push_back(SetSingleCamera(guid));
	}
	for (unsigned int i = 0; i < numCameras; i++) {
		StartCamera(cams.at(i));
	}
	ofstream cameraFd;
	cameraFd.open(cameraFile);
	cameraFd << "Number of cameras detected: " << numCameras << endl;
	while (cameraFlg) {
		string str;
		for (unsigned int i = 0; i < numCameras; i++) {
			capture(cams.at(i), id, str);
			cameraFd << str << endl;
		}
		id++;
		this_thread::sleep_for(chrono::milliseconds(SLEEP_TIME));
	}
	for (unsigned int i = 0; i < numCameras; i++) {
		StopAndDisconnectCamera(cams.at(i));
	}
}

void dataFunc() {
	ofstream obdFd;
	obdFd.open(obdFile);
	// Serial* SP = new Serial("\\\\.\\COM10");    // adjust as needed
	Serial* SP = new Serial("\\\\.\\COM3");
	if (SP->IsConnected())
		printf("Connected\n");
	char incomingData[256] = "";			// don't forget to pre-allocate memory
											// printf("%s\n",incomingData);
	int dataLength = 255;
	int readResult = 0;
	while (SP->IsConnected()) {
		readResult = SP->ReadData(incomingData, dataLength);
		// printf("Bytes read: (0 means no data available) %i\n",readResult);
		incomingData[readResult] = 0;
		string data(incomingData);
		// printf("%s", incomingData);
		auto timeStamp = chrono::system_clock::now();
		time_t cTimeStamp = chrono::system_clock::to_time_t(timeStamp);
		obdFd << "TimeStamp: " << ctime(&cTimeStamp) << " id: " << id << " data: " << data << endl;
	}
}

int main(int argc, _TCHAR* argv[]) {
	thread cameraThread(control, CAMERA);
	thread obdThread(control, OBD);
	cin.get();
	// cameraFlg is used to stop the cameras.
	cameraFlg = 0;
	PrintBuildInfo();
	// Since this application saves images in the current folder
	// we must ensure that we have permission to write to this folder.
	// If we do not have permission, fail right away.
	FILE* tempFile = fopen("test.txt", "w+");
	if (tempFile == NULL)
	{
		cout << "Failed to create file in current folder.  Please check permissions." << endl;
		return -1;
	}
	fclose(tempFile);
	remove("test.txt");
	cameraThread.join();
	obdThread.join();
	return 0;
}