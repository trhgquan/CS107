#include "SectorReader.h"
#include "NTFS_VolumeBootRecord.h"
#include "FAT32_VolumeBootRecord.h"
#include "MasterBootRecord.h"
#include "Utility.h"
#include "FAT.h"
//#include "Entry.h"
#include "RDET.h"
#include "AbstractFormat.h"
#include <iostream>


void testMBR() {
	/*This is how to read Master Boot Record (MBR), but this project doesn't need to read MBR :'(((( */
	//Create Master Boot Record, because the sector to read MBR is always fixed,
	//	so we do not need to read those sector by hand, it's already read in constructor
	MasterBootRecord MBR;
	std::cout << MBR.toString() << "\n\n";

	//Get the boot sector from the first partition table in MBR
	//	(NOTE: THAT IS THE VOLUME BOOT RECORD IN THE FIRST PRIMARY DRIVE: C:\ DRIVE)
	SectorReader reader(L"\\\\.\\PhysicalDrive0",
	MBR.partitionTables().at(0).relativeSector());

	//Load the sector to parse data
	NTFS_VolumeBootRecord NTFS_VBR(reader.sector());

	//Print data
	std::cout << NTFS_VBR.toString() << "\n";
	
}

void testNTFS() {

	//Tutorial to use NTFS_VolumeBootRecord to read data
	//	from Volume Boot Record in C:\ drive which run on NTFS format
	// Second param = 0 because the boot sector in C:\ drive is in sector 0th
	SectorReader reader2(L"\\\\.\\C:", 0);
	NTFS_VolumeBootRecord NTFS_VBR2(reader2.sector());

	//Print the data
	std::cout << NTFS_VBR2.toString() << "\n";	//This is the same result with line 26

	unsigned int test = NTFS_VBR2.EBPB().MFTClusterNumber() * NTFS_VBR2.BPB()->sectorPerCluster();
	SectorReader reader3(reader2.drive(), test, 1024);
	for (int i = 0; i < 1024; ++i) {
		std::cout << reader3.sector()[i];
	}
	std::cout << std::endl;
}

void testFAT32() {
	AbstractFormat format;
	format.run(L"\\\\.\\G:");
}

int main() {

	//testMBR();
	//testNTFS();
	testFAT32();
	

	system("PAUSE");
	return 0;
}