#include "FormatFactory.h"
#include "FAT32_Format.h"
#include "NTFS_Format.h"
#include "SectorReader.h"
#include <iostream>

//API
void FormatFactory::run(LPCWSTR drive) { _run(drive); }

void FormatFactory::_run(LPCWSTR drive) {
	//read the first 512 bytes in drive
	SectorReader reader(drive, 0);

	
	//Get VBR for information
	VolumeBootRecord VBR(reader.sector());
	
	try {
		//If OEM_ID doesn't contain "NTFS" => FAT32 format
		if (VBR.OEM_ID().find("NTFS", 0) == std::string::npos)
		{
			_prototypes.at(FAT32_FORMAT)->read(drive);
		}

		else
		{
			_prototypes.at(NTFS_FORMAT)->read(drive);
		}
	}
	catch (const std::exception e) {
		std::cout << "Doesn't exist this drive !\n";
	}
}

FormatFactory::FormatFactory()
{
	_prototypes.push_back(new FAT32_Format());
	_prototypes.push_back(new NTFS_Format());
}


FormatFactory::~FormatFactory()
{
	for (AbstractFormat* format : _prototypes) 
	{
		delete format;
	}
}
