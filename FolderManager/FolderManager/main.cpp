#include "SectorReader.h"
#include "NTFS_VolumeBootRecord.h"
#include "FAT32_VolumeBootRecord.h"
#include "MasterBootRecord.h"
#include "Utility.h"
#include "FAT.h"
#include "Entry.h"

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
	SectorReader reader2(L"\\\\.\\D:", 0 * DEFAULT_BUFFER_SIZE);

	NTFS_VolumeBootRecord NTFS_VBR2(reader2.sector());

	//Print the data
	std::cout << NTFS_VBR2.toString() << "\n";	//This is the same result with line 26
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

	//Print first 100 bytes in FAT
	for (int i = 0; i < 100; ++i)
	{
		std::cout << (unsigned int)fat.data()[i] << " ";
	}
	std::cout << std::endl;


	//Print raw data from RDET
	int length = (RDET.second - RDET.first + 1) *FAT32_VBR.BPB()->bytesPerSector();
	SectorReader reader4(reader3.drive(), RDET.first, length);
	int h = length / AbstractEntry::bytesPerEntry();
	std::vector<LongFilename> dummy;
	for (int i = 0; i < h; ++i)
	{
		BYTE* buffer = reader4.sector() + (AbstractEntry::bytesPerEntry() * i);
		if (0xE5 != buffer[0])
		{
			while (0x0F == buffer[0xB]) {
				LongFilename lfn(buffer);
				dummy.push_back(lfn);
				++i;
				buffer = reader4.sector() + (AbstractEntry::bytesPerEntry() * i);
			}

			Entry entry(buffer, dummy);
			dummy.clear();
		}
	}
	std::cout << std::endl;

}

int main() {

	//testMBR();
	//testNTFS();
	testFAT32();
	

	system("PAUSE");
	return 0;
}