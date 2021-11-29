#pragma once
#ifndef _ABSTRACT_ENTRY_H_
#define _ABSTRACT_ENTRY_H_
#include <string>
#include <windows.h>

class AbstractEntry {

protected: //private attribute
	static const unsigned int _bytesPerEntry = 32;	//number of bytes per entry
	unsigned int _firstByte;	//to detect the first empty entry: _firstByte = 0x0
	unsigned int _attribute;	//to dectect the type of entry: LFN/File/Folder/....

protected: //private utilites
	virtual void _modulateName(BYTE*&);

public: //getter
	static const unsigned int bytesPerEntry();
	virtual std::string name();	//always return ""
	virtual unsigned int firstByte();
	virtual unsigned int attribute();

public:
	AbstractEntry();
	AbstractEntry(BYTE*&);
	virtual ~AbstractEntry();
};



#endif // !_ABSTRACT_ENTRY_H_

