// SerialPort.cpp : main project file.

#include "stdafx.h"
#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include "Serial.h"
#include <string>
#include <thread>
#include <fstream>
#include "interpData.h"
#include <windows.h>

#define CAMERA 0
#define OBD_SPEED 1
#define OBD_STEERING_WHEEL 2
#define SLEEP_TIME 100

using namespace std;

volatile long id = 0;
volatile int cameraFlg = 0;

string cameraFile = "camera.txt";
string swAngleFile = "swAngle.txt";
string speedFile = "speed.txt";

void control(int);
void cameraFunc();
void swAngleFunc();
void speedFunc();
void testInterpData();

void control(int tag) {
	if (tag == CAMERA) {
		cameraFunc();
	}
	else if (tag == OBD_SPEED) {
		speedFunc();
	}
	else {
		swAngleFunc();
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

void swAngleFunc() {
	ofstream fd;
	fd.open(swAngleFile);
	// Modify this for corresponding port.
	Serial* sp = new Serial("\\\\.\\COM3");
	if (sp->IsConnected()) {
		cout << "Connected" << endl;
	}
	string command = "ATZ \r";
	sp->WriteData((char*)command.c_str(), command.size());
	Sleep(1000);
	command = "ATCRA 025 \r";
	sp->WriteData((char*)command.c_str(), command.size());
	Sleep(1000);
	command = "ATMA \r";
	sp->WriteData((char*)command.c_str(), command.size());
	Sleep(1000);
	vector<unsigned char> vec;
	char incomingData[1] = "";
	int dataLength = 1;
	while (sp->IsConnected()) {
		int rtn = sp->ReadData(incomingData, dataLength);
		if (incomingData[0] == '\r') {
			int angle = getSteeringWheelAngle(vec);
			cout << angle << endl;
			fd << angle << endl;
			vec.clear();
		}
		else {
			vec.push_back(incomingData[0]);
		}
	}
}

void speedFunc() {
	ofstream fd;
	fd.open(speedFile);
	// Modify this for corresponding port.
	Serial* sp = new Serial("\\\\.\\COM4");
	if (sp->IsConnected()) {
		cout << "Connected" << endl;
	}
	string command = "ATZ \r";
	sp->WriteData((char*)command.c_str(), command.size());
	Sleep(1000);
	command = "ATCRA 0AA \r";
	sp->WriteData((char*)command.c_str(), command.size());
	Sleep(1000);
	command = "ATMA \r";
	sp->WriteData((char*)command.c_str(), command.size());
	Sleep(1000);
	vector<unsigned char> vec;
	char incomingData[1] = "";
	int dataLength = 1;
	while (sp->IsConnected()) {
		int rtn = sp->ReadData(incomingData, dataLength);
		if (incomingData[0] == '\r') {
			int angle = getSpeed(vec);
			cout << angle << endl;
			fd << angle << endl;
			vec.clear();
		}
		else {
			vec.push_back(incomingData[0]);
		}
	}
}
/*
void dataFunc(int tag) {
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
*/
/*
void testInterpData() {
	vector<unsigned char> vec;
	vec.push_back('0');
	vec.push_back('F');
	vec.push_back(' ');
	vec.push_back('0');
	vec.push_back('0');
	vec.push_back(' ');
	vec.push_back('1');
	vec.push_back('F');
	vec.push_back(' ');
	vec.push_back('F');
	vec.push_back('F');
	vec.push_back(' ');
	vec.push_back('7');
	vec.push_back('8');
	vec.push_back(' ');
	vec.push_back('7');
	vec.push_back('8');
	vec.push_back(' ');
	vec.push_back('7');
	vec.push_back('8');
	vec.push_back(' ');
	vec.push_back('7');
	vec.push_back('8');
	vec.push_back(' ');
	vec.push_back('B');
	vec.push_back('9');

	cout << getSteeringWheelAngle(vec) << endl;
	cin.get();
}
*/

int main(int argc, char* argv[]) {
	thread cameraThread(control, CAMERA);
	thread obdSpeed(control, OBD_SPEED);
	thread obdSteeringWheel(control, OBD_STEERING_WHEEL);
	cameraFlg = 1;
	cameraThread.join();
	obdSpeed.join();
	obdSteeringWheel.join();
	// testInterpData();
	return 0;
}

