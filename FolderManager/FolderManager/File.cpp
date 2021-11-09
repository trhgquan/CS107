#include "File.h"
#include <sstream>

//Getter
std::string File::name() { return _name; };
std::string File::status() { return _status; };
int File::size() { return _size; };
std::pair<int, int> File::sectors() { return _sectors; };

//API
std::string File::toString(int level) { return _toString(level); }

std::string File::_toString(int level) {
	std::stringstream builder;
	const std::string space(' ', level);	//make a space with level ' ' characters 

	builder << space << "- Name: " << _name << "\n";
	builder << space << "\t+ Status: " << _status << "\n";
	
	//Only print _size when file is not a folder
	if ("Folder" != _status)
	{
		builder << space << "\t+ Size: " << _size << "\n";
	}

	builder << space << "\t+ Sectors: " << _sectors.first;
	int afterFirst = _sectors.first + 1;
	int last = _sectors.second;
	for (int i = afterFirst; i <= last; ++i) {
		builder << ", " << i;
	}

	return builder.str();
}

File::File()
{
	//do nothing
}


File::File(std::string name, std::string status, int size, std::pair<int, int> sectors)
{
	_name = name;
	_status = status;
	_size = size;
	_sectors = sectors;
}


File::~File()
{
	//do nothing
}
