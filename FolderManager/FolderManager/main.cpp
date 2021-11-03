#include "SectorReader.h"
#include "NTFS_VolumeBootRecord.h"
#include "MasterBootRecord.h"
#include "Utility.h"
#include <iostream>

int main() {

	/*This is how to read Master Boot Record (MBR), but this project doesn't need to read MBR :'(((( */
	/********************************************************************************************/
	/*
	MasterBootRecord MBR;
	std::cout << MBR.toString() << "\n\n";

	//Get the boot sector from the first partition table in MBR
	SectorReader reader(L"\\\\.\\PhysicalDrive0", 
		MBR.partitionTables().at(0).relativeSector()*DEFAULT_BUFFER_SIZE);

	//Load the sector to parse data
	PartitionBootSector PBS(reader.sector());

	//Print data
	std::cout << PBS.toString() << "\n";
	*/
	/********************************************************************************************/



	SectorReader reader2(L"\\\\.\\C:", 0 * DEFAULT_BUFFER_SIZE);
	NTFS_VolumeBootRecord PBS2(reader2.sector());
	std::cout << PBS2.toString() << "\n";

	system("PAUSE");
	return 0;
}