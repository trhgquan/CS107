#pragma once
#ifndef _LONG_FILENAME_H_
#define _LONG_FILENAME_H_

#include "AbstractEntry.h"

//Sub-entry
class LongFilename: public AbstractEntry {

private:	//private attribute;
	std::string _name;

private:	//private utilities;
	void _modulateName(BYTE*&) override;	//utilities to inject from bytes to name
		
public:		//getter
	std::string name() override;	

public:
	LongFilename();
	LongFilename(BYTE*&);
	~LongFilename() override;
};

#endif // !_LONG_FILENAME_H_


