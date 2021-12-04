#include "LongFilename.h"
#include <sstream>

//Getter
std::string LongFilename::name() { return _name; }

void LongFilename::_modulateName(BYTE*& entry) {
	std::stringstream builder;
	for (int i = 0x01; i < 0x0B; i += 2) { builder << (unsigned char)entry[i]; }
	for (int i = 0x0E; i < 0x1A; i += 2) { builder << (unsigned char)entry[i]; }
	for (int i = 0x1c; i < 0x20; i += 2) { builder << (unsigned char)entry[i]; }
	_name = builder.str();
}

LongFilename::LongFilename() : AbstractEntry()
{
	//do nothing
}

LongFilename::LongFilename(BYTE*& entry) : AbstractEntry(entry)
{
	_modulateName(entry);
}

LongFilename::~LongFilename()
{
	//do nothing
}
