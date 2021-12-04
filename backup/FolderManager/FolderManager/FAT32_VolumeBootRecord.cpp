#include "FAT32_VolumeBootRecord.h"
#include "Utility.h"
#include <sstream>

//Getter
FAT32_BIOSParameterBlock* FAT32_VolumeBootRecord::BPB() { return &_BPB; }
int FAT32_VolumeBootRecord::driverNumber() { return _driverNumber; }
int FAT32_VolumeBootRecord::reserved() { return _reserved; }
int FAT32_VolumeBootRecord::bootSignature() { return _bootSignature; }
int FAT32_VolumeBootRecord::volumeID() { return _volumeID; }
std::string FAT32_VolumeBootRecord::volumeLabel() { return _volumeLabel; }
std::string FAT32_VolumeBootRecord::fileSystemType() { return _fileSystemType; }

//API
void FAT32_VolumeBootRecord::readSector(BYTE* sector) { 

	//if we want to read sector again, we have to read these field, 
	//	because we don't read them in FAT32_VolumeBootRecord::_readSector(BYTE*&)
	VolumeBootRecord::_readSector(sector);

	_readSector(sector); 
}
std::string FAT32_VolumeBootRecord::toString() { return _toString(); }

void FAT32_VolumeBootRecord::_readSector(BYTE*& sector) {
	_BPB.readSector(sector);
	_driverNumber = Utility::valueInLittleEndian(sector, 0x40, 1);
	_reserved = Utility::valueInLittleEndian(sector, 0x41, 1);
	_bootSignature = Utility::valueInLittleEndian(sector, 0x42, 1);
	_volumeID = Utility::valueInLittleEndian(sector, 0x43, 4);
	_volumeLabel = Utility::getStringFromSector(sector, 0x47, 11);
	_fileSystemType = Utility::getStringFromSector(sector, 0x52, 8);
}

std::string FAT32_VolumeBootRecord::_toString() {
	std::stringstream builder;
	builder << "- FAT32 Volume Boot Record (FAT32 VBR):\n";
	builder << "- Jump instruction: 0x" << std::hex << _JumpInstruction << std::dec << "\n";
	builder << "- OEM ID: " << _OEM_ID << "\n";
	builder << _BPB.toString() << "\n";

	std::string driver = (0x00 == _driverNumber ? "floopy disks" : "hard disks");
	builder << "- Driver: " << driver << "\n";

	builder << "- Rerserved: 0x" << std::hex << _reserved << "\n";
	builder << "- Boot signature: 0x" << _bootSignature << "\n";
	builder << "- Volume serial number: 0x" << _volumeID << "\n";
	builder << "- Volume label: " << _volumeLabel << "\n";
	builder << "- File system type: " << _fileSystemType << "\n";
	builder << "- End-of-sector marker: 0x" << _endOfSectorMarker;

	return builder.str();
}

FAT32_VolumeBootRecord::FAT32_VolumeBootRecord(): VolumeBootRecord()
{
	//do nothing
}

FAT32_VolumeBootRecord::FAT32_VolumeBootRecord(BYTE* sector): VolumeBootRecord(sector) 
{
	_readSector(sector);
}

FAT32_VolumeBootRecord::~FAT32_VolumeBootRecord()
{
	//do nothing
}