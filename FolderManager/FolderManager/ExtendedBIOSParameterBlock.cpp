#include "ExtendedBIOSParameterBlock.h"
#include "Utility.h"
#include <sstream>
#include <math.h>

//Getter
int ExtendedBIOSParameterBlock::totalSector() { return _totalSector; }
int ExtendedBIOSParameterBlock::MFTClusterNumber() { return _MFTClusterNumber; }
int ExtendedBIOSParameterBlock::MFTMirrClusterNumber() { return _MFTMirrClusterNumber; }
int ExtendedBIOSParameterBlock::bytesPerFileRecordSegment() { return _bytesPerFileRecordSegment; };
int ExtendedBIOSParameterBlock::bytePerIndexBuffer() { return _bytePerIndexBuffer; };
int ExtendedBIOSParameterBlock::volumeSerialNumber() { return _volumeSerialNumber; }

//API
void ExtendedBIOSParameterBlock::readSector(BYTE*& sector) { _readSector(sector); }
std::string ExtendedBIOSParameterBlock::toString() { return _toString(); }

void ExtendedBIOSParameterBlock::_readSector(BYTE*& sector) {
	_totalSector = Utility::valueInLittleEndian(sector, 0x28, 8);
	_MFTClusterNumber = Utility::valueInLittleEndian(sector, 0x30, 8);
	_MFTMirrClusterNumber = Utility::valueInLittleEndian(sector, 0x38, 8);

	signed char bytesPerFileRecordSegmentByte = Utility::valueInLittleEndian(sector, 0x40, 1);
	_bytesPerFileRecordSegment = (int)pow(2, std::abs((int)bytesPerFileRecordSegmentByte));

	signed char bytePerIndexBufferByte = Utility::valueInLittleEndian(sector, 0x44, 1);
	_bytePerIndexBuffer = (int)pow(2, std::abs((int)bytePerIndexBufferByte));

	_volumeSerialNumber = Utility::valueInLittleEndian(sector, 0x48, 8);
}

std::string ExtendedBIOSParameterBlock::_toString() {
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

ExtendedBIOSParameterBlock::ExtendedBIOSParameterBlock()
{
	//do nothing
}

ExtendedBIOSParameterBlock::ExtendedBIOSParameterBlock(BYTE*& sector)
{
	_readSector(sector);
}

ExtendedBIOSParameterBlock::~ExtendedBIOSParameterBlock()
{
	//do nothing
}
