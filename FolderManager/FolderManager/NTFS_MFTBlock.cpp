#include <sstream>
#include "NTFS_MFTBlock.h"
#include "SectorReader.h"
#include "Utility.h"

void NTFS_MasterFileTableBlock::_readSector(BYTE* sector) {
  _signature = Utility::getStringFromSector(sector, 0x00, 4);
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

  ss << "MFT signature: " << _signature;

  return ss.str();
}

void NTFS_MasterFileTableBlock::readSector(BYTE* sector) { return _readSector(sector); }