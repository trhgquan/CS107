#pragma once
#ifndef _FORMAT_FACTORY_H_
#define _FORMAT_FACTORY_H_

//indexing for each format type in _prototypes
#define FAT32_FORMAT 0
#define NTFS_FORMAT 1

#include <vector>
#include "AbstractFormat.h"

class FormatFactory {

private:	//private attributes
	std::vector<AbstractFormat* > _prototypes;

private:	//private utilities
	void _run(LPCWSTR);

public:		//API
	void run(LPCWSTR);

public:
	FormatFactory();
	~FormatFactory();
};


#endif // _FORMAT_FACTORY_H_



