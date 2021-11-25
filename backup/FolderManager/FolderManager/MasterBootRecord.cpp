#include "MasterBootRecord.h"
#include "Utility.h"
#include "SectorReader.h"
#include <sstream>

//Getter
int MasterBootRecord::diskSignature() { return _diskSignature; };
std::vector<PartitionTable> MasterBootRecord::partitionTables() { return _partitionTables; };
int MasterBootRecord::MBR_Signature() { return _MBR_Signature; };

//API
std::string MasterBootRecord::toString() { return _toString(); }

std::string MasterBootRecord::_toString() {
	std::stringstream builder;
	builder << "- Master Boot Record (MBR):\n";
	builder << "\t+ Disk signature: " << _diskSignature << "\n\n";

	//Print data of all 4 partition tables
	for (PartitionTable tables : _partitionTables) 
	{
		builder << tables.toString() << "\n\n";
	}

	builder << "\t+ MBR signature: " << std::hex << _MBR_Signature;

	return builder.str();
}

void MasterBootRecord::_readSector(BYTE* sector) {
	_diskSignature = Utility::valueInLittleEndian(sector, 0x01B8, 4);


	for (int i = 0; i < NUMBER_OF_PRIMARY_PARTION_PER_DISK; ++i)
	{
		_partitionTables.at(i).readSector(sector);
	}

	_MBR_Signature = Utility::valueInLittleEndian(sector, 0x01FE, 2);
}

MasterBootRecord::MasterBootRecord()
{
	SectorReader reader(L"\\\\.\\PhysicalDrive0", 0 * DEFAULT_BUFFER_SIZE);

	for (int i = 0; i < NUMBER_OF_PRIMARY_PARTION_PER_DISK; ++i)
	{
		_partitionTables.emplace_back(PartitionTable(i));
	}

	_readSector(reader.sector());
}

MasterBootRecord::~MasterBootRecord()
{
	//do nothing
}