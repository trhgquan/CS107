#pragma once
#ifndef _SECTOR_READER_H_
#define _SECTOR_READER_H_

#include <windows.h>
#include <stdio.h>

#define DEFAULT_BUFFER_SIZE 512

class SectorReader {
private:
	BYTE _sector[DEFAULT_BUFFER_SIZE];
	LPCWSTR  _drive = L"";

private: //private utilites method
	int _readSector(LPCWSTR, int);	//return 0 when read successfully, and != 0 vice versa

public: //public utilities method
	int readSector(LPCWSTR, int);

public:	//Getter and setter

	BYTE* sector();				//return sector for the current read drive (highly reccommend using this to get the _sector for the fastest execution)
	BYTE* sector(LPCWSTR, int);	//return sector for a selected drive from a readPoint
	LPCWSTR drive();				//return the current read drive
	void setDrive(LPCWSTR);				//set a new drive to read
	//_sector doesn't need setter

public:	//Constructor and destructor

	SectorReader();				//default constructor
	SectorReader(LPCWSTR, int);	//parameter constructor
	~SectorReader();			//destructor

};



#endif // !_SECTOR_READER_H_



