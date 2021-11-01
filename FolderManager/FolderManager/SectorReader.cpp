#include "SectorReader.h"


/*Return 0 when successfully, else return !0*/
int SectorReader::_readSector(LPCWSTR drive, int readPoint) {
	int retCode = 0;
	DWORD bytesRead;
	HANDLE device = NULL;

	device = CreateFileW(drive,						// Drive to open
		GENERIC_READ,								// Access mode
		FILE_SHARE_READ | FILE_SHARE_WRITE,			// Share Mode
		NULL,										// Security Descriptor
		OPEN_EXISTING,								// How to create
		0,											// File attributes
		NULL);										// Handle to template

	if (INVALID_HANDLE_VALUE == device) { // Open Error
		printf("CreateFile: %u\n", GetLastError());
		return 1;
	}

	SetFilePointer(device, readPoint, NULL, FILE_BEGIN);	//Set a Point to Read

	if (!ReadFile(device, _sector, DEFAULT_BUFFER_SIZE, &bytesRead, NULL)) {
		printf("ReadFile: %u\n", GetLastError());
		return 2;
	}

	printf("Success!\n");
	return 0;
}

int SectorReader::readSector(LPCWSTR drive, int readPoint) {
	return _readSector(drive, readPoint);
}


//Getter and Setter
void SectorReader::setDrive(LPCWSTR drive) { _drive = drive; }
LPCWSTR SectorReader::drive() { return _drive; }
BYTE* SectorReader::sector() { return _sector; }
BYTE* SectorReader::sector(LPCWSTR drive, int readPoint) {

	//If _drive == drive 
	//	=> read drive doesn't change
	//	=> doesn't need to read sector again
	if (!lstrcmpW(_drive, drive)) {
		return _sector;
	}

	//if _drive != drive
	//	=>Try to read sector

	//If read sector successfully
	//	=> update new drive
	if (!_readSector(drive, readPoint)) {
		_drive = drive;
	}

	//return the new _sector if update successfully,
	//	or the old _sector in vice versa
	return  _sector;
}

//Constructor and Destructor
SectorReader::SectorReader()
{
	//do nothing
}

SectorReader::SectorReader(LPCWSTR drive, int readPoint)  {
	//If readSector successfully => _drive = drive
	if (!_readSector(drive, readPoint)) {
		_drive = drive;
	}

	//Else, _drive = L"" (The previous value)
}


SectorReader::~SectorReader()
{
	//do nothing
}
