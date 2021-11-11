#pragma once
#ifndef _ENTRY_H_
#define _ENTRY_H_

#include "FAT.h"
#include "AbstractEntry.h"
#include "LongFilename.h"
#include "File.h"
#include <vector>

class Entry: public AbstractEntry {

private:	//private attributes 
	FAT* _fat;
	std::vector<LongFilename> _LFNs;
	std::string _name;
	int _startCluster;
	int _size;

private:	//private utilities
	void _modulateName_noLFNs(BYTE*&);
	void _modulateName_LFNs(BYTE*&);
	void _modulateName(BYTE*&) override;
	void _readEntry(BYTE*&);

public:		//Getter
	
	std::vector<LongFilename> LFNs();
	std::string name() override;
	int startCluster();
	int size();

public:


public:
	Entry();
	Entry(BYTE*&, FAT*);	//For entry isn't having LFNs
	Entry(BYTE*&, FAT*, std::vector<LongFilename>);	//For entry which having LFNS
	~Entry() override; 
};


#endif // !_ENTRY_H_



