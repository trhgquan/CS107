#pragma once

#ifndef _INTERFACE_BLOCK_H_
#define _INTERFACE_BLOCK_H_

#include <string>
#include <windows.h>

//Interface for all block/sector in this project 
//	(Except: Master Boot Record (MBR), 
//	because the sector MBR read is always the first sector of "\\\\.\\PhysicalDrive0")
class IBlock {

public: //API
	virtual std::string toString() = 0;		//For output
	virtual void readSector(BYTE*) = 0;	//Inject data from sector to private attribute

public:
	virtual ~IBlock() 
	{
		//do nothing
	};
};



#endif


