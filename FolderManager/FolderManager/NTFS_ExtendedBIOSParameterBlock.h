#pragma once
#ifndef _NTFS_EXTENDED_BIOS_PARAMETER_BLOCK_H_
#define _NTFS_EXTENDED_BIOS_PARAMETER_BLOCK_H_

#include "IBlock.h"

class NTFS_ExtendedBIOSParameterBlock: public IBlock {

private://private attribute
	int _totalSector;
	int _MFTClusterNumber;
	int _MFTMirrClusterNumber;
	int _bytesPerFileRecordSegment;
	int _bytePerIndexBuffer;
	int _volumeSerialNumber;

private://private utility method
	std::string _toString();		//For output 
	void _readSector(BYTE*&);	//Inject data from sector to private attribute

public://getter
	int totalSector();
	int MFTClusterNumber();
	int MFTMirrClusterNumber();
	int bytesPerFileRecordSegment();
	int bytePerIndexBuffer();
	int volumeSerialNumber();

public://API
	std::string toString() override;		//API for _toString() 
	void readSector(BYTE*&) override;	//API for _readSector()

public://Constructor and Destructor
	NTFS_ExtendedBIOSParameterBlock();
	NTFS_ExtendedBIOSParameterBlock(BYTE*&);
	~NTFS_ExtendedBIOSParameterBlock() override;
};

#endif // !_NTFS_EXTENDED_BIOS_PARAMETER_BLOCK_H_




