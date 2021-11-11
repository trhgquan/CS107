#pragma once
#ifndef _ENTRY_H_
#define _ENTRY_H_

#include "FAT.h"
#include "AbstractEntry.h"
#include "LongFilename.h"
#include "File.h"
#include <vector>

//forward declaration to avoid circular dependencies
class SDET;

class Entry: public AbstractEntry {

private:	//private attributes 
	FAT* _fat;
	std::vector<LongFilename> _LFNs;
	std::string _name;
	int _startCluster;
	int _size;

	File _file;
	SDET* _sdet;

private:	//private utilities
	int _getStartCluster(BYTE*&);
	void _getSDET();
	void _getFile();
	void _modulateName_noLFNs(BYTE*&);
	void _modulateName_LFNs(BYTE*&);
	void _modulateName(BYTE*&) override;
	void _readEntry(BYTE*&);
	std::string _toString(int level);

public:		//Getter
	std::vector<LongFilename> LFNs();
	std::string name() override;
	int startCluster();
	int size();

	File file();
	SDET* sdet();

public:		//API
	std::string toString(int level);

public:
	Entry();
	Entry(BYTE*&, FAT*);	//For entry isn't having LFNs
	Entry(BYTE*&, FAT*, std::vector<LongFilename>);	//For entry which having LFNS
	~Entry() override; 
};


#endif // !_ENTRY_H_



