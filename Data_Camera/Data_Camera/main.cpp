// SerialPort.cpp : main project file.

#include "stdafx.h"
#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include "Serial.h"
#include <string>
#include <thread>
#include <fstream>

#define CAMERA 0
#define OBD 1
#define SLEEP_TIME 100

using namespace std;

volatile long id = 0;
volatile int cameraFlg = 0;

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
	ofstream cameraFd;
	cameraFd.open(cameraFile);
	for (;;) {
		if (cameraFlg) {
			return;
		}
		id++;
		this_thread::sleep_for(chrono::milliseconds(SLEEP_TIME));
		cameraFd << id << endl;
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
		printf("%s", incomingData);

	}
}

int main(int argc, _TCHAR* argv[]) {
	thread cameraThread(control, CAMERA);
	thread obdThread(control, OBD);
	cin.get();
	cameraFlg = 1;
	// cameraThread.join();
	// obdThread.join();
	return 0;
}