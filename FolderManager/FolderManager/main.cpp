#include "SectorReader.h"
#include "NTFS_VolumeBootRecord.h"
#include "NTFS_MasterFileTable.h"
#include "FAT32_VolumeBootRecord.h"
#include "MasterBootRecord.h"
#include "Utility.h"
#include "FormatFactory.h"
#include "FAT.h"
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

	//Now can print the boot sector of NTFS Format like this
	FormatFactory factory;
	factory.run(L"\\\\.\\D:");

	/*
	//Tutorial to use NTFS_VolumeBootRecord to read data
	//	from Volume Boot Record in C:\ drive which run on NTFS format
	SectorReader reader2(L"\\\\.\\D:", 0);

	NTFS_VolumeBootRecord NTFS_VBR2(reader2.sector());

	//Print the data
	std::cout << NTFS_VBR2.toString() << "\n";

	// Listing out all files inside disk
	NTFS_MasterFileTable MFT(NTFS_VBR2);

	int i = 0;
	try {
		SectorReader MFT_reader(reader2.drive(), MFT.startingSector() + (4 * i), 1024);

		MFT.readSector(MFT_reader.sector());

		for (auto block : MFT.MFTB()) {
			std::cout << block.toString() << '\n';
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
	*/
}

void testFAT32() {
	FormatFactory factory;
	factory.run(L"\\\\.\\G:");
}

int main() {

	//testMBR();
	testNTFS();
	//testFAT32();
	
	system("PAUSE");
	return 0;
}