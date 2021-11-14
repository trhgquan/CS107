#include <sstream>
#include "NTFS_MFTBlock.h"
#include "SectorReader.h"
#include "Utility.h"
#include <iostream>
#include <sstream>

#define uint unsigned int 

void NTFS_MasterFileTableBlock::_readSector(BYTE* sector) {
  std::string signature = Utility::getStringFromSector(sector, 0x00, 4);

  if (signature != "FILE") {
    throw std::exception("Cannot read this sector - entry header not found.");
  }

  uint entryStart = Utility::valueInLittleEndian(sector, 0x14, 2);

 // _fileSizeAllocated = Utility::valueInLittleEndian(sector, 0x1C, 4);
  _flags = Utility::valueInLittleEndian(sector, 0x16, 2);
  
  // Get createdAt, updateDataAt, updateDescriptionAt, accessAt
  uint standardInformationSize = Utility::valueInLittleEndian(sector, entryStart + 4, 4);

  // Get fileName
  uint fileNameStarting = Utility::valueInLittleEndian(sector, entryStart + standardInformationSize + 20, 2);
  uint fileNameLength = Utility::valueInLittleEndian(sector, entryStart + standardInformationSize + fileNameStarting + 64, 1);

  std::stringstream builder;
  for (unsigned int i = 0; i < 2 * fileNameLength; i += 2) {
	  int offset = entryStart + standardInformationSize + fileNameStarting + 66;
	  builder << Utility::getStringFromSector(sector, offset + i, 1);
  }
  _fileName = builder.str();


  // Get file data
  uint dataOffset = entryStart + standardInformationSize + fileNameStarting + 66 + fileNameLength * 2;

  _fileSize = Utility::valueInLittleEndian(sector, dataOffset, 4);


}

NTFS_MasterFileTableBlock::NTFS_MasterFileTableBlock() {
  // Do nothing
}

NTFS_MasterFileTableBlock::~NTFS_MasterFileTableBlock() {
  // Do nothing
}

NTFS_MasterFileTableBlock::NTFS_MasterFileTableBlock(BYTE*& sector) {
  _readSector(sector);
}

std::string NTFS_MasterFileTableBlock::toString() {
  std::stringstream ss;

  ss << "File name: " << _fileName << '\n';

  if (_flags == NTFS_MasterFileTableBlock::FILE_FLAG) {
    ss << "Type: file" << '\n';
  } else {
    ss << "Type: folder" << '\n';
  }

  return ss.str();
}

void NTFS_MasterFileTableBlock::readSector(BYTE* sector) { return _readSector(sector); }