#include "Entry.h"
#include "Utility.h"
#include <sstream>

//Getter
std::vector<LongFilename> Entry::LFNs() { return _LFNs; }
std::string Entry::name() { return _name; }
int Entry::startCluster() { return _startCluster; };
int Entry::size() { return _size; };


void Entry::_modulateName_noLFNs(BYTE*& entry) {
	std::stringstream builder;
	std::string buffer = Utility::getStringFromSector(entry, 0x00, 8);
	std::string extension = Utility::getStringFromSector(entry, 0x08, 3);
	size_t spacePos = 0;

	//If there are a space at the end of file name
	// => Get only the name before the space
	if ((spacePos = buffer.find(' ', 0)) != std::string::npos)
	{
		buffer = buffer.substr(0, spacePos);
	}

	//Get the file name
	builder << buffer;

	//If the file is archive => add '.' for extension
	if (0x20 == _attribute)
	{
		builder << ".";
	}
	else {

		//clear space on extension
		if ((spacePos = extension.find(' ', 0)) != std::string::npos)
		{
			if (0 == spacePos)
			{
				extension = "";
			}
			else
			{
				extension = extension.substr(0, spacePos);
			}
		}

	}

	//extension is just a name;
	builder << extension;
	_name = builder.str();
}

void Entry::_modulateName_LFNs(BYTE*& entry) {

	std::stringstream builder;
	std::string  buffer;
	size_t nullPos;

	//If the entry does have LFNs
	int length = _LFNs.size();

	//Get the name from LFN
	for (int i = length - 1; i >= 0; --i)
	{
		builder << _LFNs.at(i).name();
	}

	//get the name
	buffer = builder.str();

	//Get the only file + extension name behind NULL char
	if ((nullPos = buffer.find('\0', 0)) != std::string::npos)
	{
		buffer = buffer.substr(0, nullPos);
	}

	_name = buffer;
}

void Entry::_modulateName(BYTE*& entry) {

	//If the entry doesn't have LFNs
	if (0 == _LFNs.size()) {
		_modulateName_noLFNs(entry);
		return;
	}

	//else
	_modulateName_LFNs(entry);
}

void Entry::_readEntry(BYTE*& entry) {

	_startCluster = Utility::valueInLittleEndian(entry, 0x1A, 2);
	_size = Utility::valueInLittleEndian(entry, 0x1C, 4);
	_modulateName(entry);
}

Entry::Entry(): AbstractEntry()
{
	//do nothing
}


Entry::Entry(BYTE*& entry) : AbstractEntry(entry)
{
	_readEntry(entry);
}

Entry::Entry(BYTE*& entry, std::vector<LongFilename> LFNs) : AbstractEntry(entry)
{
	_LFNs = LFNs;
	_readEntry(entry);
}


Entry::~Entry()
{
	//do nothing
}
