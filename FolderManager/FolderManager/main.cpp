#include "SectorReader.h"
#include "NTFS_VolumeBootRecord.h"
#include "NTFS_MasterFileTable.h"
#include "FAT32_VolumeBootRecord.h"
#include "MasterBootRecord.h"
#include "Utility.h"
#include "FormatFactory.h"

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
	SectorReader reader2(L"\\\\.\\D:", 0);

	NTFS_VolumeBootRecord NTFS_VBR2(reader2.sector());

	//Print the data
	std::cout << NTFS_VBR2.toString() << "\n";	//This is the same result with line 26

	// Listing out all files inside disk
	NTFS_MasterFileTable MFT(NTFS_VBR2);

	int i = 26;
	try {
		SectorReader MFT_reader(reader2.drive(), MFT.startingSector() + (1024 * i), 1024);	

		MFT.readSector(MFT_reader.sector());

		for (auto block : MFT.MFTB()) {
			std::cout << block.toString() << '\n';
		}
	} catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
}

void testFAT32() {

	//Tutorial to use FAT32_VolumeBootRecord to read data 
	//	from Volume Boot Record in G:\ drive (which is Nhat Dang's USB) which run on FAT32 format

	SectorReader reader3(L"\\\\.\\G:", 0);
	FAT32_VolumeBootRecord FAT32_VBR(reader3.sector());

	//Print the data  from FAT32 Boot Sector
	std::cout << FAT32_VBR.toString() << "\n";
	FAT fat(FAT32_VBR, reader3.drive());

	std::pair<int, int> FSINFO = fat.trace(1);
	std::pair<int, int> RDET = fat.trace(2);

	unsigned int test = NTFS_VBR2.EBPB().MFTClusterNumber() * NTFS_VBR2.BPB()->sectorPerCluster();
	SectorReader reader3(reader2.drive(), test, 1024);
	for (int i = 0; i < 1024; ++i) {
		std::cout << reader3.sector()[i];
	}
	std::cout << std::endl;
}

void testFAT32() {
	FormatFactory factory;
	factory.run(L"\\\\.\\G:");
}

int main() {

	//testMBR();
	testNTFS();
	// testFAT32();
	

	system("PAUSE");
	return 0;
}