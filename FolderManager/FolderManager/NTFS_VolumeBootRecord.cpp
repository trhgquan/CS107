#include "NTFS_VolumeBootRecord.h"
#include "Utility.h"
#include <sstream>

//Getter
NTFS_BIOSParameterBlock NTFS_VolumeBootRecord::BPB() { return _BPB; }
NTFS_ExtendedBIOSParameterBlock NTFS_VolumeBootRecord::EBPB() { return _EBPB; }

//API
std::string NTFS_VolumeBootRecord::toString() { return _toString(); }
void NTFS_VolumeBootRecord::readSector(BYTE*& sector) { _readSector(sector); }

void NTFS_VolumeBootRecord::_readSector(BYTE*& sector) {
	//((VolumeBootRecord*)this)->readSector(sector);	//No need, cause we already read these field on constructor
	_BPB.readSector(sector);
	_EBPB.readSector(sector);
}

std::string NTFS_VolumeBootRecord::_toString() {
	std::stringstream builder;
	builder << "- Partition Boot Sector (PBS):\n";
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
