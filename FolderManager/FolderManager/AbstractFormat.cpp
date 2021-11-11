#include "AbstractFormat.h"
#include "SectorReader.h"
#include "VolumeBootRecord.h"
#include "FAT32_Format.h"

//API
void AbstractFormat::run(LPCWSTR drive) { _run(drive); }

void AbstractFormat::_run(LPCWSTR drive) {

	//read the first 512 bytes in drive
	SectorReader reader(drive, 0);	

	//Get VBR for information
	VolumeBootRecord VBR(reader.sector());

	//If OEM_ID doesn't contain "NTFS" => FAT32 format
	if (VBR.OEM_ID().find("NTFS", 0) == std::string::npos)  {
		FAT32_Format format;
		format.run(drive);
	}
	else
	{
		//NTFS_Format format;
		//format.run(drive);
	}
}

AbstractFormat::AbstractFormat()
{
	//do nothing
}


AbstractFormat::~AbstractFormat()
{
	//do nothing
}
