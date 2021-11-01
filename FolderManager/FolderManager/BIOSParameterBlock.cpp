#include "BIOSParameterBlock.h"
#include "Utility.h"
#include <sstream>

//Getter;
int BIOSParameterBlock::bytesPerSector() {return _bytesPerSector; }
int BIOSParameterBlock::sectorPerCluster() { return _sectorPerCluster; }
char* BIOSParameterBlock::mediaDiscriptor() { return _mediaDiscriptor; }
int BIOSParameterBlock::sectorPerTrack() {return _sectorPerTrack; }
int BIOSParameterBlock::numberOfHeads() { return _numberOfHeads; }
int BIOSParameterBlock::hiddenSectors() { return _hiddenSectors; }

//API
void BIOSParameterBlock::readSector(BYTE*& sector) { _readSector(sector); }
std::string BIOSParameterBlock::toString() { return _toString(); }

//Inject data from sector to private attribute
void BIOSParameterBlock::_readSector(BYTE*& sector) {
	_bytesPerSector = Utility::valueInLittleEndian(sector, 0x0B, 2);
	_sectorPerCluster = Utility::valueInLittleEndian(sector, 0x0D, 1);
	_sectorPerTrack = Utility::valueInLittleEndian(sector, 0x18, 2);
	_numberOfHeads = Utility::valueInLittleEndian(sector, 0x1A, 2);
	_hiddenSectors = Utility::valueInLittleEndian(sector, 0x1C, 4);

}

std::string BIOSParameterBlock::_toString() {
	std::stringstream builder;
	builder << "- BIOS Parameter Block (BPB):\n";
	builder << "\t+ Bytes per sector: " << _bytesPerSector << "\n";
	builder << "\t+ Sectors per cluster: " << _sectorPerCluster << "\n";
	builder << "\t+ Type of drive: " << _mediaDiscriptor << "\n";
	builder << "\t+ Sectors per track: " << _sectorPerTrack << "\n";
	builder << "\t+ Number of heads: " << _numberOfHeads << "\n";
	builder << "\t+ The index of sector preciding this partition: " << _hiddenSectors;
	return builder.str();
}

BIOSParameterBlock::BIOSParameterBlock()
{
	//do nothing
}

BIOSParameterBlock::BIOSParameterBlock(BYTE*& sector) 
{
	_readSector(sector);
}

BIOSParameterBlock::~BIOSParameterBlock()
{
	//do nothing
}
