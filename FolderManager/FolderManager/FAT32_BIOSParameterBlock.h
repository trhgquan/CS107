#pragma once
#ifndef _FAT32_BIOS_PARAMETER_BLOCK_H_
#define _FAT32_BIOS_PARAMETER_BLOCK_H_

#include "BIOSParameterBlock.h"

class FAT32_BIOSParameterBlock: public BIOSParameterBlock {

private:	//private attribue
	int _numberOfSectorsForBootSector;
	int _numberOfFATs;
	int _numberOfSectorsInVolumes;
	int _sectorPerFAT;
	int _extFlag;
	std::string _FAT32_version;
	int _RDET_clusterNumber;
	int _FSINFO_clusterNumber;
	int _backupBootSectorClusterNumber;
	int _reserved;

private:	//private utilities
	std::string _toString() override;	//For output 
	void _readSector(BYTE*&) override;	//Inject data from sector to private attribute

public:		//getter
	int numberOfSectorsForBootSector();
	int numberOfFATs();
	int numberOfSectorsInVolumes();
	int sectorPerFAT();
	int extFlag();
	std::string FAT32_version();
	int RDET_clusterNumber();
	int FSINFO_clusterNumber();
	int backupBootSectorClusterNumber();
	int reserved();

public:		//API
	std::string toString() override;	//API for _toString()
	void readSector(BYTE*) override;	//API for _readSector(BYTE*&)

public:
	FAT32_BIOSParameterBlock();
	FAT32_BIOSParameterBlock(BYTE*);
	~FAT32_BIOSParameterBlock();
};

#endif // !_FAT32_BIOS_PARAMETER_BLOCK_H_



