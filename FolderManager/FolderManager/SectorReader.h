#pragma once
#ifndef _SECTOR_READER_H_
#define _SECTOR_READER_H_

#include <windows.h>
#include <stdio.h>

#define DEFAULT_BUFFER_SIZE 512

class SectorReader {
private:
	BYTE* _sector = nullptr;
	LPCWSTR  _drive = L"";
	int _numberBytesRead;

private: //private utilites method
	int _readSector(LPCWSTR, unsigned int);	//return 0 when read successfully, and != 0 vice versa

public: //public utilities method
	int readSector(LPCWSTR, unsigned int);	//API for _readSector(LPCWSTR, unsigned int)

public:	//Getter and setter
	BYTE* sector();				//return sector for the current read drive
	LPCWSTR drive();				//return the current read drive
	int numberBytesRead();		//return the number of bytes to read
	void setDrive(LPCWSTR);				//set a new drive to read
	void setNumberBytesRead(int); //set new number of bytes to read

public:	//Constructor and destructor

	SectorReader();				//default constructor
	SectorReader(LPCWSTR,unsigned int, int numberBytesRead = DEFAULT_BUFFER_SIZE);	//parameter constructor
	~SectorReader();			//destructor

};



#endif // !_SECTOR_READER_H_



