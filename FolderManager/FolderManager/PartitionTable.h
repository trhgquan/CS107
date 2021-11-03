#pragma once
#ifndef _PARTITION_TABLE_H_
#define _PARTITION_TABLE_H_

#include "IBlock.h"

class PartitionTable: public IBlock{

private: //private attribute

	//Index of partition table (0-indexing)
	int _index = 0;

	//Partition structure
	int _status;
	int _startingHead;
	int _startingSector;
	int _startingCylinder;
	int _systemID;
	int _endingHead;
	int _endingSector;
	int _endingCylinder;
	unsigned int _relativeSector;
	unsigned int _totalSector;

private://private utitlity
	std::string _toString();		//For output 
	void _readSector(BYTE*&);		//Inject data from sector to private attribute


public: //getter

	//Index of partition table (0-indexing)
	int index();	

	//Partition structure
	int status();
	int startingHead();
	int startingSector();
	int startingCylinder();
	int systemID();
	int endingHead();
	int endingSector();
	int endingCylinder();
	unsigned int relativeSector();
	unsigned int totalSector();

	//need a setter for _index
	void setIndex(int);

public: //API
	std::string toString() override;		//API for _toString() 
	void readSector(BYTE*&) override;		//API for _readSector() 

public:	//Constructor and Destructor
	PartitionTable();			//default constructor
	PartitionTable(int);		//parameter consructor
	~PartitionTable() override;	//destructor
};


#endif // !_PARTITION_TABLE_H_




