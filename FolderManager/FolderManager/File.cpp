#include "File.h"
#include <sstream>

//Getter
std::string File::name() { return _name; };
std::string File::status() { return _status; };
int File::size() { return _size; };
std::pair<int, int> File::sectors() { return _sectors; };
std::string File::content() { return _content; }

//API
std::string File::toString(int level) { return _toString(level); }

std::string File::_toString(int level) {
	std::stringstream builder;
	const std::string space(level, '\t');	//make a space with level ' ' characters 

	builder << space << "- Name: " << _name << "\n";
	builder << space << " + Status: " << _status << "\n";
	builder << space << " + Sectors: " << _sectors.first << ", ... , " << _sectors.second;
	
	//Only print _size and _content when file is not a folder
	if ("Folder" != _status)
	{
		builder << "\n" << space << " + Size: " << _size;

	}

	//Only print _content when file extension is .txt
	int nameLength = _name.length();
	std::string extension = _name.substr(nameLength - 3, 3);	//3 = "txt".length()
	if ("txt" == extension || "TXT" == extension)
	{
		builder << "\n" << space << " + .txt content:\n";
		builder << space << "   " << _content;
	}

	return builder.str();
}

File::File()
{
	//do nothing
}


File::File(std::string name, std::string status, 
	int size, std::pair<int, int> sectors, std::string content) {
	_name = name;
	_status = status;
	_size = size;
	_sectors = sectors;
	_content = content;
}


File::~File()
{
	//do nothing
}
