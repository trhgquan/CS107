#pragma once
#ifndef _PARTITION_BOOT_SECTOR_H_
#define _PARTITION_BOOT_SECTOR_H_

#include "BIOSParameterBlock.h"
#include "ExtendedBIOSParameterBlock.h"

class PartitionBootSector: public IBlock {

private://private attribute
	int _JumpInstruction;
	std::string _OEM_ID;
	BIOSParameterBlock _BPB;			//Bios Parameter Block
	ExtendedBIOSParameterBlock _EBPB;	//Extended Bios Parameter Block
	int _endOfSectorMarker;

private://private utility method
	std::string _toString();		//For output 
	void _readSector(BYTE*&);		//Inject data from sector to private attribute

public:	//Getter
	int JumpInstruction();
	std::string OEM_ID();
	BIOSParameterBlock BPB();			
	ExtendedBIOSParameterBlock EBPB();	
	int endOfSectorMarker();

public: //API
	std::string toString() override;	//API for _toString()
	void readSector(BYTE*&) override;	//API for _readSector()

public:
	PartitionBootSector();
	PartitionBootSector(BYTE*);
	~PartitionBootSector() override;
};

#endif // !_PARTITION_BOOT_SECTOR_H_



