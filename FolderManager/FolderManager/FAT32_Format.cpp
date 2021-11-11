#include "FAT32_Format.h"
#include "SectorReader.h"
#include <iostream>

//API
void FAT32_Format::run(LPCWSTR drive) { _run(drive); }

void FAT32_Format::_removeMemory() {

	if (_vbr) { 
		delete _vbr; 
		_vbr = nullptr;
	}

	if (_fat) { 
		delete _fat; 
		_fat = nullptr;
	}

	if (_rdet) { 
		delete _rdet; 
		_rdet = nullptr;
	}
}

void FAT32_Format::_run(LPCWSTR drive) {

	//read the first 512 bytes in drive
	SectorReader reader(drive, 0);
	_removeMemory();
	_vbr = new FAT32_VolumeBootRecord(reader.sector());
	_fat = new FAT(*_vbr, reader.drive());
	_rdet = new RDET(_fat, _fat -> bootSector().BPB()->RDET_clusterNumber());

	//print data
	std::cout << _vbr->toString() << "\n\n";	//Print boot sector information
	std::cout << _rdet->toString() << "\n";	//Print index tree
}

FAT32_Format::FAT32_Format()
{
	//do nothing
}

FAT32_Format::FAT32_Format(LPCWSTR drive) 
{
	_run(drive);
}

FAT32_Format::~FAT32_Format()
{
	_removeMemory();
}
