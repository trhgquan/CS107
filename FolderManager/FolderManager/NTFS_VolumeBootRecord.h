#pragma once
#ifndef _NTFS_VOLUME_BOOT_RECORD_H_
#define _NTFS_VOLUME_BOOT_RECORD_H_

#include "NTFS_BIOSParameterBlock.h"
#include "NTFS_ExtendedBIOSParameterBlock.h"
#include "VolumeBootRecord.h"

class NTFS_VolumeBootRecord: public VolumeBootRecord {

private://private attribute
	NTFS_BIOSParameterBlock _BPB;			//Bios Parameter Block
	NTFS_ExtendedBIOSParameterBlock _EBPB;	//Extended Bios Parameter Block

private://private utility method
	std::string _toString() override;		//For output 
	void _readSector(BYTE*&) override;		//Inject data from sector to private attribute

public:	//Getter
	NTFS_BIOSParameterBlock BPB() override;			
	NTFS_ExtendedBIOSParameterBlock EBPB();	

public: //API
	std::string toString() override;	//API for _toString()
	void readSector(BYTE*) override;	//API for _readSector()

public:
	NTFS_VolumeBootRecord();
	NTFS_VolumeBootRecord(BYTE*);
	~NTFS_VolumeBootRecord() override;
};

#endif // !_NTFS_VOLUME_BOOT_RECORD_H_



