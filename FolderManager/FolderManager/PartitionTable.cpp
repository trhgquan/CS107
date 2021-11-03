#include "PartitionTable.h"
#include "Utility.h"
#include <sstream>

//Getter
int PartitionTable::index() { return _index; }
int PartitionTable::status() { return _status; };
int PartitionTable::startingHead() { return _startingHead; };
int PartitionTable::startingSector() { return _startingSector; };
int PartitionTable::startingCylinder() { return _startingCylinder; };
int PartitionTable::systemID() { return _systemID; };
int PartitionTable::endingHead() { return _endingHead; };
int PartitionTable::endingSector() { return _endingSector; };
int PartitionTable::endingCylinder() { return _endingCylinder; };
unsigned int PartitionTable::relativeSector() { return _relativeSector; };
unsigned int PartitionTable::totalSector() { return _totalSector; };

//Setter for index
void PartitionTable::setIndex(int index) {
	_index = index;
}

//API
std::string PartitionTable::toString() { return _toString(); }				//For output 
void PartitionTable::readSector(BYTE*& sector) { _readSector(sector); }		//Inject data from sector to private attribute

std::string PartitionTable::_toString() {
	std::stringstream builder;
	builder << "\t+ Partition Table (idx = " << _index << "):\n";
	builder << "\t\t* Status: " << (0x80 == _status ? "Bootable" : 
		(0x00 == _status ? "Non-Bootable" : "Invalid")) << "\n";

	builder << "\t\t* Starting head: " << _startingHead << "\n";
	builder << "\t\t* Starting sector: " << _startingSector << "\n";
	builder << "\t\t* Starting cylinder: " << _startingCylinder << "\n";
	builder << "\t\t* System ID: 0x" << std::hex << _systemID << std::dec << "\n";
	builder << "\t\t* Ending head: " << _endingHead << "\n";
	builder << "\t\t* Ending sector: " << _endingSector << "\n";
	builder << "\t\t* Ending cylinder: " << _endingCylinder << "\n";
	builder << "\t\t* Relative sector: " << _relativeSector << "\n";
	builder << "\t\t* Total sector: " << _totalSector;

	return builder.str();
}

void PartitionTable::_readSector(BYTE*& sector) {
	//index is already read

	int startOffset = 0x01BE + 16 * _index;
	_status = Utility::valueInLittleEndian(sector,startOffset, 1);
	_startingHead = Utility::valueInLittleEndian(sector, startOffset + 1, 1);
	_startingSector = Utility::valueInLittleEndian(sector, startOffset + 2, 1);
	_startingCylinder = Utility::valueInLittleEndian(sector, startOffset + 3, 1);
	_systemID = Utility::valueInLittleEndian(sector, startOffset + 4, 1);;
	_endingHead = Utility::valueInLittleEndian(sector, startOffset + 5, 1);
	_endingSector = Utility::valueInLittleEndian(sector, startOffset + 6, 1);
	_endingCylinder = Utility::valueInLittleEndian(sector, startOffset + 7, 1);
	_relativeSector = Utility::valueInLittleEndian(sector, startOffset + 8, 4);
	_totalSector = Utility::valueInLittleEndian(sector, startOffset + 12, 4);
}

PartitionTable::PartitionTable()
{
	//do nothing
}


PartitionTable::PartitionTable(int index) {
	_index = index;
}


PartitionTable::~PartitionTable()
{
	//do nothing
}
