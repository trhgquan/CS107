#pragma once
#ifndef _BIOS_PARAMETER_BLOCK_H_
#define _BIOS_PARAMETER_BLOCK_H_

#include "IBlock.h"

class BIOSParameterBlock: public IBlock {

private: //Private attribute
	int _bytesPerSector;
	int _sectorPerCluster;
	char* _mediaDiscriptor = "Fixed Disk";
	int _sectorPerTrack;
	int _numberOfHeads;
	int _hiddenSectors;

private: //Private utility method
	std::string _toString();	//For output 
	void _readSector(BYTE*&);	//Inject data from sector to private attribute

public:	//Getter 
	int bytesPerSector();
	int sectorPerCluster();
	char* mediaDiscriptor();
	int sectorPerTrack();
	int numberOfHeads();
	int hiddenSectors();

public: //API
	std::string toString() override;	//API for _toString() 
	void readSector(BYTE*&) override;	//API for _readSector()

public:
	BIOSParameterBlock();
	BIOSParameterBlock(BYTE*&);
	~BIOSParameterBlock() override; 
};

#endif // !_BIOS_PARAMETER_BLOCK_H_




