#include "FAT32_BIOSParameterBlock.h"
#include "Utility.h"
#include <sstream>
#include <bitset>

//Getter
int FAT32_BIOSParameterBlock::numberOfSectorsBeforeFAT() { return _numberOfSectorsBeforeFAT; }
int FAT32_BIOSParameterBlock::numberOfFATs() { return _numberOfFATs; }
int FAT32_BIOSParameterBlock::numberOfSectorsInVolumes() { return _numberOfSectorsInVolumes; }
int FAT32_BIOSParameterBlock::sectorPerFAT() { return _sectorPerFAT; }
int FAT32_BIOSParameterBlock::extFlag() { return _extFlag; }
std::string FAT32_BIOSParameterBlock::FAT32_version() { return _FAT32_version; }
int FAT32_BIOSParameterBlock::RDET_clusterNumber() { return _RDET_clusterNumber; }
int FAT32_BIOSParameterBlock::FSINFO_clusterNumber() { return _FSINFO_clusterNumber; }
int FAT32_BIOSParameterBlock::backupBootSectorClusterNumber() { return _backupBootSectorClusterNumber; }
int FAT32_BIOSParameterBlock::reserved() { return _reserved; }

//API
void FAT32_BIOSParameterBlock::readSector(BYTE* sector) 
{
	//These attributes which the parent class have are the similar attributes 
	//	of FAT32 format and NTFS format
	BIOSParameterBlock::_readSector(sector);

	_readSector(sector);
}
std::string FAT32_BIOSParameterBlock::toString() { return _toString(); }

void FAT32_BIOSParameterBlock::_readSector(BYTE*& sector) {
	_numberOfSectorsBeforeFAT = Utility::valueInLittleEndian(sector, 0xE, 2);
	_numberOfFATs = Utility::valueInLittleEndian(sector, 0x10, 1);
	_numberOfSectorsInVolumes = Utility::valueInLittleEndian(sector, 0x20, 4);
	_sectorPerFAT = Utility::valueInLittleEndian(sector, 0x24, 4);
	_extFlag = Utility::valueInLittleEndian(sector, 0x28, 2);
	
	//Get FAT Version
	int minor = Utility::valueInLittleEndian(sector, 0x2B, 1);
	int major = Utility::valueInLittleEndian(sector, 0x2A, 1);
	std::stringstream builder;
	builder << major << "." << minor;
	_FAT32_version = builder.str();

	_RDET_clusterNumber = Utility::valueInLittleEndian(sector, 0x2C, 4);
	_FSINFO_clusterNumber = Utility::valueInLittleEndian(sector, 0x30, 2);
	_backupBootSectorClusterNumber = Utility::valueInLittleEndian(sector, 0x32, 2);
	_reserved = Utility::valueInLittleEndian(sector, 0x34, 12);
}

std::string FAT32_BIOSParameterBlock::_toString() {
	std::stringstream builder;
	builder << ((BIOSParameterBlock)*this).toString() << "\n";
	builder << "\t+ Number of sectors for Boot Sector: " << _numberOfSectorsBeforeFAT << "\n";
	builder << "\t+ Number of FATs: " << _numberOfFATs << "\n";
	builder << "\t+ Number of sectors in volume: " << _numberOfSectorsInVolumes << "\n";
	builder << "\t+ Number of sectors per FAT: " << _sectorPerFAT << "\n";
	builder << "\t+ Flag: " << std::bitset<16>(_extFlag) << "\n";
	builder << "\t+ FAT32 version: " << _FAT32_version << "\n";
	builder << "\t+ RDET cluster index: " << _RDET_clusterNumber << "\n";
	builder << "\t+ FSINFO cluster index: " << _FSINFO_clusterNumber << "\n";
	builder << "\t+ Backup Boot Sector cluster index: " << _backupBootSectorClusterNumber << "\n";
	builder << "\t+ Reserved: " << std::hex << _reserved;
	return builder.str();
}

FAT32_BIOSParameterBlock::FAT32_BIOSParameterBlock(): BIOSParameterBlock()
{
	//do nothing
}

FAT32_BIOSParameterBlock::FAT32_BIOSParameterBlock(BYTE* sector) : BIOSParameterBlock(sector)
{
	_readSector(sector);
}

FAT32_BIOSParameterBlock::~FAT32_BIOSParameterBlock()
{
	//do nothing
}
