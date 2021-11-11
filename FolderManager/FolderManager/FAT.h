#pragma once
#ifndef _FAT_H_
#define _FAT_H_

#include "FAT32_VolumeBootRecord.h"

#define CLUSTER_BYTE 4			//FAT32 table group 4 bytes to locate a cluster

class FAT {

private:	//private attributes
	int _FAT_size;						//Number of bytes in FAT
	LPCWSTR _drive;						//name of the drive which is used
	FAT32_VolumeBootRecord _bootSector;	//the boot sector
	BYTE* _data = nullptr;				//data in FAT 

private:	//private static utilities
	static bool _isEOF(unsigned int);				//check if a cluster is a OEF-cluster

private:	//private utilities

	//Param: int: start cluster index to trace in the FAT
	//output:	int: .first = start SECTOR index
	//			int: .second = end CLUSTER index
	std::pair<int, int> _trace(int);

	//After using setter to set attributes, use this to re-initialize data in class
	void _initData();

public:		//Getter and Setter
	BYTE* data();
	int FAT_size();
	LPCWSTR drive();
	void setBootSector(const FAT32_VolumeBootRecord&);
	void setDrive(const LPCWSTR&);

public:		//API
	std::pair<int, int> trace(int);		//API for _trace(int)
	void initData();					//API for _initData();

public:		//constructor and destructor
	FAT();
	
	//Param: 
	// FAT32_VolumeBootRecord: boot sector
	// LPCWSTR: drive name
	FAT(FAT32_VolumeBootRecord, LPCWSTR);

	~FAT();
};



#endif // !_FAT_H_
