#pragma once
#ifndef _FILE_H_
#define _FILE_H_

#include <string>

/*
	To print the data of a 
*/
class File {

protected://attributes
	std::string _name;		//the name of file/folder (including extension)
	std::string _status;	//the type of file, folder, etc
	int _size;				//calculate in byte
	std::pair<int, int> _sectors;	//_sectors.first = the start sector, _sectors.second = the last sector
	std::string _content;	//content only to print data in .txt file

private: //private utilities
	
	//Example: C:/ have 2 folder: a and b
	//a is empty; b has file test.txt;
	//	=> level(a) = 0
	//	=> level(b) = 0
	//		=>> level(test.txt) = 1
	// level is the number of folders before of a file/folder
	virtual std::string _toString(int level) final;

public:	//getter
	virtual std::string name() final;
	virtual std::string status() final;
	virtual int size() final;
	virtual std::pair<int, int> sectors() final;
	virtual std::string content();

public: //API

	
	virtual std::string toString(int level) final;

public:	//constructor/destructor
	File();
	File(std::string, std::string, int, std::pair<int, int>, std::string content = "");
	virtual ~File();
};


#endif // !_FILE_H_



