#include "FAT32_Format.h"
#include "SectorReader.h"
#include <iostream>

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

void FAT32_Format::_read(LPCWSTR drive) {

	//read the first 512 bytes in drive
	SectorReader reader(drive, 0);
	_removeMemory();
	_vbr = new FAT32_VolumeBootRecord(reader.sector());
	_fat = new FAT(*_vbr, reader.drive());
	_rdet = new RDET(_fat, _fat -> bootSector().BPB()->RDET_clusterNumber());

	//print data
	std::cout << "*************FAT32 FORMAT*************\n";
	std::cout << "*******BOOT SECTOR INFORMATION*******\n\n";
	std::cout << _vbr->toString() << "\n\n";	//Print boot sector information
	std::cout << "*************DIRECTORIES*************\n\n";
	std::cout << _rdet->toString() << "\n";	//Print index tree
}

FAT32_Format::FAT32_Format()
{
	//do nothing
}

FAT32_Format::FAT32_Format(LPCWSTR drive) 
{
	_read(drive);
}

FAT32_Format::~FAT32_Format()
{
	_removeMemory();
}
