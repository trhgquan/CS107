#include "VolumeBootRecord.h"
#include "Utility.h"
#include <sstream>

//Getter
int VolumeBootRecord::JumpInstruction() { return _JumpInstruction; }
std::string VolumeBootRecord::OEM_ID() { return _OEM_ID; }
int VolumeBootRecord::endOfSectorMarker() { return _endOfSectorMarker; }
BIOSParameterBlock* VolumeBootRecord::BPB() { return nullptr; }	//return an empty BPB

//API
std::string VolumeBootRecord::toString() { return _toString(); }
void VolumeBootRecord::readSector(BYTE* sector) { _readSector(sector); }

std::string VolumeBootRecord::_toString() {
	std::stringstream builder;
	builder << "- Volume Boot Record (VBR):\n";
	builder << "- Jump instruction: 0x" << std::hex << _JumpInstruction << std::dec << "\n";
	builder << "- End-of-sector marker: 0x" << std::hex << _endOfSectorMarker;
	return builder.str();
}

void VolumeBootRecord::_readSector(BYTE*& sector) {
	_JumpInstruction = Utility::valueInLittleEndian(sector, 0x00, 3);
	_OEM_ID = Utility::getStringFromSector(sector, 0x03, 8);
	_endOfSectorMarker = Utility::valueInLittleEndian(sector, 0x01FE, 2);
}

VolumeBootRecord::VolumeBootRecord() 
{
	//do nothing
}

VolumeBootRecord::VolumeBootRecord(BYTE* sector) 
{	
	_readSector(sector);
}

VolumeBootRecord::~VolumeBootRecord() 
{
	//do nothing
}