#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "interpData.h"

using namespace std;

int hex2dec(string hexStr) {
	return (int)strtol(hexStr.c_str(), 0, 16);
}
// http://www.cplusplus.com/forum/beginner/41657/
string hexStr2binStr(string sHex)
{
	string sReturn = "";
	for (int i = 0; i < sHex.length(); ++i)
	{
		switch (sHex[i])
		{
			case '0': sReturn.append("0000"); break;
			case '1': sReturn.append("0001"); break;
			case '2': sReturn.append("0010"); break;
			case '3': sReturn.append("0011"); break;
			case '4': sReturn.append("0100"); break;
			case '5': sReturn.append("0101"); break;
			case '6': sReturn.append("0110"); break;
			case '7': sReturn.append("0111"); break;
			case '8': sReturn.append("1000"); break;
			case '9': sReturn.append("1001"); break;
			case 'a':
			case 'A': sReturn.append("1010"); break;
			case 'b':
			case 'B': sReturn.append("1011"); break;
			case 'c':
			case 'C': sReturn.append("1100"); break;
			case 'd':
			case 'D': sReturn.append("1101"); break;
			case 'e':
			case 'E': sReturn.append("1110"); break;
			case 'f':
			case 'F': sReturn.append("1111"); break;
		}
	}
	return sReturn;
}
// http://stackoverflow.com/questions/2689028/need-fastest-way-to-convert-2s-complement-to-decimal-in-c
int binTwosComplementToSignedDecimal(string binStr, int significantBits)
{
	char* binary = (char*)binStr.c_str();
	int power = pow(2, significantBits - 1);
	int sum = 0;
	int i;

	for (i = 0; i < significantBits; ++i)
	{
		if (i == 0 && binary[i] != '0')
		{
			sum = power * -1;
		}
		else
		{
			sum += (binary[i] - '0') * power;//The -0 is needed
		}
		power /= 2;
	}

	return sum;
}

int getSteeringWheelAngle(vector<unsigned char> byteArr) {
	stringstream ss;
	ss << "";
	for (unsigned char uc : byteArr) {
		ss << uc;
	}
	string byteStr = ss.str();
	if (byteStr.size() == 3) {
		string dataStr = byteStr.substr(0, 2);
		return hex2dec(dataStr);
	}
	else {
		string first = byteStr.substr(0, 2);
		string second = byteStr.substr(3, 2);
		if (first.compare("00") == 0) {
			return hex2dec(second);
		}
		else if (first.compare("0E") == 0) {
			stringstream tmp;
			string binStr = hexStr2binStr(second);
			tmp << "10" << binStr;
			binStr = tmp.str();
			return binTwosComplementToSignedDecimal(binStr, 10);
		}
		else {
			stringstream tmp;
			string binStr = hexStr2binStr(second);
			tmp << "1" << binStr;
			binStr = tmp.str();
			return binTwosComplementToSignedDecimal(binStr, 9);
		}
	}
}

int getSpeed(vector<unsigned char> byteArr) {
	return 0;
}

