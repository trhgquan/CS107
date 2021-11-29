#include "NTFS_VolumeBootRecord.h"
#include "Utility.h"
#include <sstream>

//Getter
NTFS_BIOSParameterBlock* NTFS_VolumeBootRecord::BPB() { return &_BPB; }
NTFS_ExtendedBIOSParameterBlock NTFS_VolumeBootRecord::EBPB() { return _EBPB; }

//API
std::string NTFS_VolumeBootRecord::toString() { return _toString(); }
void NTFS_VolumeBootRecord::readSector(BYTE* sector) { 

	//if we want to read sector again, we have to read these field, 
	//	because we don't read them in NTFS_VolumeBootRecord::_readSector(BYTE*&)
	VolumeBootRecord::_readSector(sector);	

	_readSector(sector); 
}

void NTFS_VolumeBootRecord::_readSector(BYTE*& sector) {
	//VolumeBootRecord::_readSector(sector);		//No need, cause we already read these field on constructor
	_BPB.readSector(sector);
	_EBPB.readSector(sector);
}

std::string NTFS_VolumeBootRecord::_toString() {
	std::stringstream builder;
	builder << "- NTFS Volume Boot Record (NTFS VBR):\n";
	builder << "- Jump instruction: 0x" << std::hex << _JumpInstruction << std::dec << "\n";
	builder << "- OEM ID: " << _OEM_ID << "\n";
	builder << _BPB.toString() << "\n";
	builder << _EBPB.toString() << "\n";
	builder << "- End-of-sector marker: 0x" << std::hex << _endOfSectorMarker;
	return builder.str();
}

NTFS_VolumeBootRecord::NTFS_VolumeBootRecord(): VolumeBootRecord()
{
	//do nothing
}

NTFS_VolumeBootRecord::NTFS_VolumeBootRecord(BYTE* sector): VolumeBootRecord(sector)
{
	_readSector(sector);
}


NTFS_VolumeBootRecord::~NTFS_VolumeBootRecord()
{
	//do nothing
}
