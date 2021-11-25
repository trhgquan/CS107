#include "NTFS_ExtendedBIOSParameterBlock.h"
#include "Utility.h"
#include <sstream>
#include <math.h>

//Getter
int NTFS_ExtendedBIOSParameterBlock::totalSector() { return _totalSector; }
int NTFS_ExtendedBIOSParameterBlock::MFTClusterNumber() { return _MFTClusterNumber; }
int NTFS_ExtendedBIOSParameterBlock::MFTMirrClusterNumber() { return _MFTMirrClusterNumber; }
int NTFS_ExtendedBIOSParameterBlock::bytesPerFileRecordSegment() { return _bytesPerFileRecordSegment; };
int NTFS_ExtendedBIOSParameterBlock::bytePerIndexBuffer() { return _bytePerIndexBuffer; };
int NTFS_ExtendedBIOSParameterBlock::volumeSerialNumber() { return _volumeSerialNumber; }

//API
void NTFS_ExtendedBIOSParameterBlock::readSector(BYTE* sector) { _readSector(sector); }
std::string NTFS_ExtendedBIOSParameterBlock::toString() { return _toString(); }

void NTFS_ExtendedBIOSParameterBlock::_readSector(BYTE*& sector) {
	_totalSector = Utility::valueInLittleEndian(sector, 0x28, 8);
	_MFTClusterNumber = Utility::valueInLittleEndian(sector, 0x30, 8);
	_MFTMirrClusterNumber = Utility::valueInLittleEndian(sector, 0x38, 8);

	signed char bytesPerFileRecordSegmentByte = Utility::valueInLittleEndian(sector, 0x40, 1);
	_bytesPerFileRecordSegment = (int)pow(2, std::abs((int)bytesPerFileRecordSegmentByte));

	signed char bytePerIndexBufferByte = Utility::valueInLittleEndian(sector, 0x44, 1);
	_bytePerIndexBuffer = (int)pow(2, std::abs((int)bytePerIndexBufferByte));

	_volumeSerialNumber = Utility::valueInLittleEndian(sector, 0x48, 8);
}

std::string NTFS_ExtendedBIOSParameterBlock::_toString() {
	std::stringstream builder;
	builder << "- Extended BIOS Parameter Block (EBPB):\n";
	builder << "\t+ Total sectors: " << _totalSector << "\n";
	builder << "\t+ MFT cluster number: " << _MFTClusterNumber << "\n";
	builder << "\t+ Mirrored MFT cluster numbber: " << _MFTMirrClusterNumber << "\n";
	builder << "\t+ Bytes per File Record Segment: " << _bytesPerFileRecordSegment << "\n";
	builder << "\t+ Bytes per Index Buffer: " << _bytePerIndexBuffer << "\n";
	builder << "\t+ Volume serial number: " << std::hex << _volumeSerialNumber;
	return builder.str();
}

NTFS_ExtendedBIOSParameterBlock::NTFS_ExtendedBIOSParameterBlock()
{
	//do nothing
}

NTFS_ExtendedBIOSParameterBlock::NTFS_ExtendedBIOSParameterBlock(BYTE*& sector)
{
	_readSector(sector);
}

NTFS_ExtendedBIOSParameterBlock::~NTFS_ExtendedBIOSParameterBlock()
{
	//do nothing
}
