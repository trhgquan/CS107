#ifndef _VOLUME_BOOT_RECORD_H_
#define _VOLUME_BOOT_RECORD_H_

#include "IBlock.h"
#include "BIOSParameterBlock.h"

//Parent for VBR of NTFS and VBR of FAT32
class VolumeBootRecord: public IBlock {

protected://Protect attributes for inheriting
	int _JumpInstruction;
	std::string _OEM_ID;
	int _endOfSectorMarker;

protected://Protect utilities for inheriting
	virtual std::string _toString();		//For output 
	virtual void _readSector(BYTE*&);		//Inject data from sector to private attribute

public:	//Getter
	int JumpInstruction();
	std::string OEM_ID();
	virtual BIOSParameterBlock BPB();	//NTFS_BPB and FAT32_BPB need to override this method
	int endOfSectorMarker();

public:	//API
	virtual std::string toString() override;	//API for _toString()
	virtual void readSector(BYTE*) override;	//API for _readSector()

public:	//Constructor/destructor
	VolumeBootRecord();
	VolumeBootRecord(BYTE*);
	~VolumeBootRecord() override;
	
};

#endif // !_VOLUME_BOOT_RECORD_H_
