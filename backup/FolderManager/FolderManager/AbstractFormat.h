#pragma once
#ifndef _ABSTRACT_FORMAT_H_
#define _ABSTRACT_FORMAT_H_

#include <windows.h>


class AbstractFormat {

protected:	//protected utilities
	virtual void _read(LPCWSTR);			//Get all the file/folder information in a drive 

public: //API
	void read(LPCWSTR);	//API for _run(LPCWSTR)

public:
	AbstractFormat();
	virtual ~AbstractFormat();
};


#endif // !_ABSTRACT_FORMAT_H_



