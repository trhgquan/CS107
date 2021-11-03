#include "SectorReader.h"
#include "NTFS_VolumeBootRecord.h"
#include "MasterBootRecord.h"
#include "Utility.h"
#include <iostream>

int main() {

	/*This is how to read Master Boot Record (MBR), but this project doesn't need to read MBR :'(((( */
	/********************************************************************************************/
	/*
	//Create Master Boot Record, because the sector to read MBR is always fixed, 
	//	so we do not need to read those sector by hand, it's already read in constructor
	MasterBootRecord MBR;
	std::cout << MBR.toString() << "\n\n";

	//Get the boot sector from the first partition table in MBR 
	//	(NOTE: THAT IS THE VOLUME BOOT RECORD IN THE FIRST PRIMARY DRIVE: C:\ DRIVE)
	SectorReader reader(L"\\\\.\\PhysicalDrive0", 
		MBR.partitionTables().at(0).relativeSector()*DEFAULT_BUFFER_SIZE);

	//Load the sector to parse data
	NTFS_VolumeBootRecord NTFS_VBR(reader.sector());

	//Print data
	std::cout << NTFS_VBR.toString() << "\n";
	*/
	/********************************************************************************************/


	//Tutorial to use NTFS_VolumeBootRecord to read data 
	//	from Volume Boot Record in C:\ drive which run on NTFS format
	SectorReader reader2(L"\\\\.\\C:", 0 * DEFAULT_BUFFER_SIZE);
	NTFS_VolumeBootRecord NTFS_VBR2(reader2.sector());

	//Print the data
	std::cout << NTFS_VBR2.toString() << "\n";	//This is the same result with line 26

	system("PAUSE");
	return 0;
}