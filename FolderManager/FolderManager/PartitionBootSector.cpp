#include "PartitionBootSector.h"
#include "Utility.h"
#include <sstream>

//Getter
int PartitionBootSector::JumpInstruction() { return _JumpInstruction; }
std::string PartitionBootSector::OEM_ID() { return _OEM_ID; }
BIOSParameterBlock PartitionBootSector::BPB() { return _BPB; }
ExtendedBIOSParameterBlock PartitionBootSector::EBPB() { return _EBPB; }
int PartitionBootSector::endOfSectorMarker() { return _endOfSectorMarker; }

//API
std::string PartitionBootSector::toString() { return _toString(); }
void PartitionBootSector::readSector(BYTE*& sector) { _readSector(sector); }

void PartitionBootSector::_readSector(BYTE*& sector) {
	_JumpInstruction = Utility::valueInLittleEndian(sector, 0x00, 3);
	_OEM_ID= Utility::getStringFromSector(sector, 0x03, 8);
	_BPB.readSector(sector);
	_EBPB.readSector(sector);
	_endOfSectorMarker = Utility::valueInLittleEndian(sector, 0x01FE, 2);

}

std::string PartitionBootSector::_toString() {
	std::stringstream builder;
	builder << "- Partition Boot Sector (PBS):\n";
	builder << "- Jump instruction: " << std::hex << _JumpInstruction << "\n";
	builder << "- OEM ID: " << _OEM_ID << "\n";
	builder << _BPB.toString() << "\n";
	builder << _EBPB.toString() << "\n";
	builder << "- End-of-sector marker: " << std::hex << _endOfSectorMarker;
	return builder.str();
}

PartitionBootSector::PartitionBootSector()
{
	//do nothing
}

PartitionBootSector::PartitionBootSector(BYTE* sector)
{
	_readSector(sector);
}


PartitionBootSector::~PartitionBootSector()
{
	//do nothing
}
