#include "SectorReader.h"

/*
 WARNING: SectorReader::_readSector(LPCWSTR drive, unsigned int sectorIndex) only execute correctly when 
 the number of bytes per sector is 512 (byte)
*/

/*Return 0 when successfully, else return !0*/
/*Read all _numberBytesRead bytes from the sector which have sectorIndex in drive and store in _sector*/
/*Sector is 0-indexing*/
int SectorReader::_readSector(LPCWSTR drive, unsigned int sectorIndex) {
	int retCode = 0;
	DWORD bytesRead = _numberBytesRead;
	HANDLE device = NULL;

	//Get the low word and high word of the sector byte
	unsigned long long fullWord = sectorIndex * DEFAULT_BUFFER_SIZE;
	unsigned int lowWord = fullWord & 0xFFFFFFFF;	//First 32bit of full word
	long highWord = (fullWord & ~(0xFFFFFFFF)) >> 32;	//Second 32bit of full word

	device = CreateFileW(drive,						// Drive to open
		GENERIC_READ,								// Access mode
		FILE_SHARE_READ | FILE_SHARE_WRITE,			// Share Mode
		NULL,										// Security Descriptor
		OPEN_EXISTING,								// How to create
		0,											// File attributes
		NULL);										// Handle to template

	if (INVALID_HANDLE_VALUE == device) { // Open Error
		printf("CreateFile: %u\n", GetLastError());
		CloseHandle(device);
		return 1;
	}

	SetFilePointer(device, lowWord, &highWord, FILE_BEGIN);	//Set a Point to Read

	if (!ReadFile(device, _sector, _numberBytesRead, &bytesRead, NULL)) {
		printf("ReadFile: %u\n", GetLastError());
		CloseHandle(device);
		return 2;
	}

	CloseHandle(device);
	//printf("Success!\n");
	return 0;
}

int SectorReader::readSector(LPCWSTR drive,unsigned int sectorIndex, int numberByteRead) {
	if (_numberBytesRead != numberByteRead) {
		_numberBytesRead = numberByteRead;

		//Delete current _sector
		if (_sector)
		{
			delete[]_sector;
		}

		//Allocate new data
		_sector = new BYTE[_numberBytesRead + 2];
	}

	return _readSector(drive, sectorIndex);
}


//Getter and Setter
void SectorReader::setDrive(LPCWSTR drive) { _drive = drive; }
void SectorReader::setNumberBytesRead(int numberBytesRead) { 
	_numberBytesRead = numberBytesRead; 

	//Delete current _sector
	if (_sector) 
	{ 
		delete[]_sector; 
	}

	//Allocate new data
	_sector = new BYTE[_numberBytesRead + 2];
}
LPCWSTR SectorReader::drive() { return _drive; }
int SectorReader::numberBytesRead() { return _numberBytesRead; }
BYTE* SectorReader::sector() { return _sector; }

//Constructor and Destructor
SectorReader::SectorReader()
{
	//do nothing
}

SectorReader::SectorReader(LPCWSTR drive, unsigned int sectorIndex, int numberBytesRead)  {

	_numberBytesRead = numberBytesRead;
	_sector = new BYTE[_numberBytesRead + 2];

	//If readSector successfully => _drive = drive
	if (!_readSector(drive, sectorIndex)) {
		_drive = drive;
	}

	//Else, _drive = L"" (The previous value)
}


SectorReader::~SectorReader()
{

	//Delete unused memory
	if (_sector) {
		delete[]_sector;
		_sector = nullptr;
	}
}
