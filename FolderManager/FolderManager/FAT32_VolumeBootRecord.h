#pragma once
#ifndef _FAT32_VOLUME_BOOT_RECORD_H_
#define _FAT32_VOLUME_BOOT_RECORD_H_

#include "VolumeBootRecord.h"
#include "FAT32_BIOSParameterBlock.h"

class FAT32_VolumeBootRecord : public VolumeBootRecord {

private://Private attributes
	FAT32_BIOSParameterBlock _BPB;
	int _driverNumber;
	int _reserved;
	int _bootSignature;
	int _volumeID;
	std::string _volumeLabel;
	std::string _fileSystemType;

private://Private utilities
	std::string _toString();		//For output 
	void _readSector(BYTE*&);		//Inject data from sector to private attribute

public: //Getter
	BIOSParameterBlock BPB() override;
	int driverNumber();
	int reserved();
	int bootSignature();
	int volumeID();
	std::string volumeLabel();
	std::string fileSystemType();

public: //API
	std::string toString() override;		//For output 
	void readSector(BYTE*) override;		//Inject data from sector to private attribute

public: //Constructor/Destructor
	FAT32_VolumeBootRecord();
	FAT32_VolumeBootRecord(BYTE*);
	~FAT32_VolumeBootRecord() override;

};

#endif // !_FAT32_VOLUME_BOOT_RECORD_H_
