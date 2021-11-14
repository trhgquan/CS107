#include "NTFS_Format.h"
#include "NTFS_MasterFileTable.h"
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
	std::cout << "*************NTFS FORMAT*************\n";
	std::cout << "*******BOOT SECTOR INFORMATION*******\n\n";
	std::cout << _vbr->toString() << "\n\n";	//Print boot sector information

	// Print first file
	std::cout << "*******FIRST FILE IN DISK*******\n\n";
	NTFS_MasterFileTable MFT(*_vbr);
	int startingSectorIndex = 0;

	SectorReader reader1(reader.drive(), MFT.startingSector() + startingSectorIndex, 1024);

	MFT.readSector(reader1.sector());

	for (auto i : MFT.MFTB()) {
		std::cout << i.toString() << '\n';
	}
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
