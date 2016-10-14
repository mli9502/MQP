// SerialPort.cpp : main project file.

#include "stdafx.h"
#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include "Serial.h"
#include <string>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	printf("Welcome to the serial test app!\n\n");

	// Serial* SP = new Serial("\\\\.\\COM10");    // adjust as needed
	Serial* SP = new Serial("\\\\.\\COM3");
	cin.get();
	if (SP->IsConnected())
		printf("We're connected");

	char incomingData[256] = "";			// don't forget to pre-allocate memory
											//printf("%s\n",incomingData);
	int dataLength = 255;
	int readResult = 0;
	cin.get();
	while (SP->IsConnected())
	{
		readResult = SP->ReadData(incomingData, dataLength);
		// printf("Bytes read: (0 means no data available) %i\n",readResult);
		incomingData[readResult] = 0;

		printf("%s", incomingData);
	}
	return 0;
}