#include "AbstractFormat.h"
#include "SectorReader.h"
#include "VolumeBootRecord.h"
#include "FAT32_Format.h"

//API
void AbstractFormat::read(LPCWSTR drive) { _read(drive); }

void AbstractFormat::_read(LPCWSTR drive) 
{
	//do nothing
}

AbstractFormat::AbstractFormat()
{
	//do nothing
}


AbstractFormat::~AbstractFormat()
{
	//do nothing
}
