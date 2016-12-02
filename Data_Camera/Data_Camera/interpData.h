#pragma once
#include <vector>

using namespace std;

int getSteeringWheelAngle(vector<unsigned char>);
int getSpeed(vector<unsigned char>);
// Convert hex string to decimal int.
int hex2dec(string);
// Convert hex string to binary string.
string hexStr2binStr(string);
// Convert 2's comp binary string to decimal int.
int binTwosComplementToSignedDecimal(string binStr, int significantBits);