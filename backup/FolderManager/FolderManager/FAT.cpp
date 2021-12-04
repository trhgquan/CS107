#include "FAT.h"
#include "SectorReader.h"
#include "Utility.h"

//Getter and Setter
BYTE* FAT::data() { return _data; }
int FAT::FAT_size() { return _FAT_size; }
LPCWSTR FAT::drive() { return _drive; };
FAT32_VolumeBootRecord FAT::bootSector() { return _bootSector; };
void FAT::setBootSector(const FAT32_VolumeBootRecord& bootSector) { _bootSector = bootSector; };
void FAT::setDrive(const LPCWSTR& drive) { _drive = drive; };

//API
std::pair<int, int> FAT::trace(int startClusterIndex) { return _trace(startClusterIndex); };
void FAT::initData() { 

	//Delete while exist data 
	if (_data) {
		delete[]_data;
		_data = nullptr;
	}

	//Re-initialize
	_initData(); 
};

//Because EOF values in FAT32 in range [0xFFFFFF8:0xFFFFFFF]
//	We see that the first digit must be in range [0x8:0xF]
bool FAT::_isEOF(unsigned int cluster) {
	const int EOFMask = 0xFFFFFFF0;	//Make a Mask to get the first digit
	int lastHalfByte = cluster & (~EOFMask);	//Get the first digit (and some dummy value from the second digit to seventh digit)
	return (lastHalfByte >= 0x8 && lastHalfByte <= 0xF);	//Return true if the first digit in range [0x8; 0xF]
}

std::pair<int, int> FAT::_trace(int startClusterIndex) {
	int endClusterIndex = startClusterIndex;
	int data = 0;

	//Iteration until data is EOF cluster
	do {
		data = Utility::valueInLittleEndian(
			_data, CLUSTER_BYTE*endClusterIndex, CLUSTER_BYTE
		);

		++endClusterIndex;
	} while (!_isEOF(data));
	--endClusterIndex;		

	//Get the start data sector
	int startDataSector = _bootSector.BPB()->numberOfSectorsBeforeFAT()
		+ _bootSector.BPB()->numberOfFATs() * _bootSector.BPB()->sectorPerFAT();
		
	//The name say all
	int sectorPerCluster = _bootSector.BPB()->sectorPerCluster();

	//Some easy formula to get start sector index and end sector index from
	//start cluster index and end cluster index
	int startSectorIndex = startDataSector + (startClusterIndex - 2) * sectorPerCluster;
	int endSectorIndex = startSectorIndex + (endClusterIndex - startClusterIndex)* sectorPerCluster + (sectorPerCluster - 1);

	return std::make_pair(startSectorIndex, endSectorIndex);
}
 
void FAT::_initData() {

	//Saved some already haved attributes from Boot Sector to local variables for faster execution
	//BIOSParameterBlock BPB = _bootSector.BPB();
	int sectorPerFat = _bootSector.BPB()->sectorPerFAT();
	int bytesPerSector = _bootSector.BPB()->bytesPerSector();
	int sectorBeforeFAT = _bootSector.BPB()->numberOfSectorsBeforeFAT();

	//Get the size of FAT
	_FAT_size = sectorPerFat * bytesPerSector;

	//Read the FAT sector
	SectorReader reader(_drive, sectorBeforeFAT, _FAT_size);
	/*
	reader.setDrive(_drive);
	reader.setNumberBytesRead(_FAT_size);
	reader.readSector(_drive, bytesPerSector * sectorBeforeFAT);*/

	//Save FAT data
	_data = new BYTE[_FAT_size + 2];
	memcpy(_data, reader.sector(), sizeof(BYTE)*sectorPerFat * bytesPerSector);
}


FAT::FAT()
{
	//do nothing
}

FAT::FAT(FAT32_VolumeBootRecord bootSector, LPCWSTR drive) {

	//use swallow copy, because there are not any pointer in FAT32_VolumeBootRecord class
	_bootSector = bootSector;

	_drive = drive;
	_initData();
}

FAT::~FAT() {
	if (_data) {
		delete[]_data;
		_data = nullptr;
	}
}
