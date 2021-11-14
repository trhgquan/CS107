#include "NTFS_Format.h"
#include "SectorReader.h"
#include <iostream>

void NTFS_Format::_removeMemory() {

	if (_vbr) {
		delete _vbr;
		_vbr = nullptr;
	}

}

void NTFS_Format::_read(LPCWSTR drive) {

	//read the first 512 bytes in drive
	SectorReader reader(drive, 0);
	_removeMemory();
	_vbr = new NTFS_VolumeBootRecord(reader.sector());
	

	//print data
	std::cout << _vbr->toString() << "\n\n";	//Print boot sector information
}

NTFS_Format::NTFS_Format()
{
	//do nothing
}

NTFS_Format::NTFS_Format(LPCWSTR drive)
{
	_read(drive);
}

NTFS_Format::~NTFS_Format()
{
	_removeMemory();
}
