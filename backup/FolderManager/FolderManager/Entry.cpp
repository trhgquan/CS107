#include "Entry.h"
#include "SDET.h"
#include "Utility.h"
#include "SectorReader.h"
#include <sstream>

//Getter
std::vector<LongFilename> Entry::LFNs() { return _LFNs; }
std::string Entry::name() { return _name; }
int Entry::startCluster() { return _startCluster; };
int Entry::size() { return _size; };
File Entry::file() { return _file; };
SDET* Entry::sdet() { return _sdet; }

//API
std::string Entry::toString(int level) { return _toString(level); }

std::string Entry::_toString(int level) {
	std::stringstream builder;
	builder << _file.toString(level);
	if (_sdet) {
		for (Entry* entry : _sdet->entries()) 
		{
			builder << "\n\n" << entry -> toString(level + 1);
		}
	}

	return builder.str();
}

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

void Entry::_getSDET() {
	
	//If the entry has a folder => get its SDEt
	if (0x10 == _attribute)
	{
		_sdet = new SDET(_fat, _startCluster);
	}	
}

void Entry::_getFile() {

	//Get the attribute string (only support for File and Folder)
	std::string attribute;
	if (0x20 == _attribute) attribute = "File";
	else if (0x10 == _attribute) attribute = "Folder";

	//Get the sectors for file
	std::pair<int, int> sectors = _fat->trace(_startCluster);

	//Get the content for the file
	std::string content;

	//If the entry has a file => if it's a .txt file, get it content
	if (0x20 == _attribute) {
		int dotPos = _name.find('.', 0);
		std::string extension = _name.substr(dotPos + 1, 3);

		if ("txt" == extension || "TXT" == extension) {
			int size = (sectors.second - sectors.first + 1) *_fat->bootSector().BPB()->bytesPerSector();
			
			//Must read size characters from drive, because number of bytes read = i * 512 (i >= 1)
			SectorReader reader(_fat->drive(), sectors.first, size);

			//get only _size characters from _sector
			char* buffer = new char[_size + 2];
			memcpy(buffer, reader.sector(), _size * sizeof(char));
			buffer[_size] = '\0';
			content = std::string(buffer);

			delete[]buffer;
		}
	}

	_file = File(_name, attribute, _size, sectors, content);

}

int Entry::_getStartCluster(BYTE*& entry) {
	int lowWord = Utility::valueInLittleEndian(entry, 0x1A, 2);
	int highWord = Utility::valueInLittleEndian(entry, 0x14, 2);
	return (highWord << 8) + lowWord;
}

void Entry::_readEntry(BYTE*& entry) {


	_startCluster = _getStartCluster(entry);
	_size = Utility::valueInLittleEndian(entry, 0x1C, 4);
	_modulateName(entry);
	_getSDET();
	_getFile();

}

Entry::Entry(): AbstractEntry()
{
	//do nothing
}


Entry::Entry(BYTE*& entry, FAT* fat) : AbstractEntry(entry) {
	_fat = fat;
	_readEntry(entry);
}

Entry::Entry(BYTE*& entry, FAT* fat, std::vector<LongFilename> LFNs) : AbstractEntry(entry) {
	_fat = fat;
	_LFNs = LFNs;
	_readEntry(entry);
}


Entry::~Entry()
{
	if (_sdet) {
		delete _sdet;
		_sdet = nullptr;
	}
}
