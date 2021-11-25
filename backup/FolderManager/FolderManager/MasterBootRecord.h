#pragma once
#ifndef _MASTER_BOOT_RECORD_
#define _MASTER_BOOT_RECORD_

#define NUMBER_OF_PRIMARY_PARTION_PER_DISK 4

#include "PartitionTable.h"
#include <vector>

/*The only structure which isn't inheritted from IBlock, 
because the read sector of Master Boot Record is fixed (the first sector of "\\\\.\\PhysicalDrive0" )*/
class MasterBootRecord {

private://private attribute
	int _diskSignature;
	std::vector<PartitionTable> _partitionTables;	//There are only 4 partition tables
	int _MBR_Signature;

private://private utitlity
	std::string _toString();		//For output 
	void _readSector(BYTE*);		//Inject data from sector to private attribute
	
public:	//getter
	int diskSignature();
	std::vector<PartitionTable> partitionTables();
	int MBR_Signature();

public:	//API
	std::string toString();	//API for _toString() 

public:	//constructor/destructor
	MasterBootRecord();				//default constructor
	~MasterBootRecord();			//destructor
};

#endif // !_MASTER_BOOT_RECORD_

