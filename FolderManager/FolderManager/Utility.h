#pragma once
#ifndef _UTILITY_H_
#define _UTILITY_H_

#include<windows.h>
#include<string>

class Utility {
private:
	static const int HEX = 16;
	static const int DEC = 10;

public:
	//Return the value of sector[offset:(offset + length - 1)] in little endian format
	//Example: 
	//	sector[3] = 0x01
	//	sector[4] = 0x02
	//	sector[5] = 0x03
	//		=> int valueInLittleEndian(sector, 3, 3) = 0x030201 
	//			= sector[5]*16^(2*2) + sector[4] * 16(2*1) + sector[3] * 16(2*0)
	static int valueInLittleEndian(BYTE* sector, int offset, int length);
	
	//return a string = sector[offset: offset + length - 1]
	static std::string getStringFromSector(BYTE* sector, int offset, int length);
};

#endif // !_UTILITY_H_