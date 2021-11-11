#include "AbstractEntry.h"
#include "Utility.h"

//Getter
const unsigned int AbstractEntry::bytesPerEntry() { return _bytesPerEntry; };
std::string AbstractEntry::name() { return ""; }
unsigned int AbstractEntry::firstByte() { return _firstByte; };
unsigned int AbstractEntry::attribute() { return _attribute; };

void AbstractEntry::_modulateName(BYTE*& entry)  {
	//do nothing
	//for overriding
}

AbstractEntry::AbstractEntry()
{
	//do nothing
}

AbstractEntry::AbstractEntry(BYTE*& entry) {
	_firstByte = Utility::valueInLittleEndian(entry, 0x0, 1);
	_attribute = Utility::valueInLittleEndian(entry, 0xB, 1);
}

AbstractEntry::~AbstractEntry()
{
	//do nothing
}
