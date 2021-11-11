#include "NTFS_MasterFileTable.h"
#include "NTFS_MFTBlock.h"
#include "NTFS_ExtendedBIOSParameterBlock.h"
#include "NTFS_BIOSParameterBlock.h"
#include "SectorReader.h"
#include "Utility.h"
#include <sstream>

NTFS_MasterFileTable::NTFS_MasterFileTable() {
  // Do nothing
}

NTFS_MasterFileTable::~NTFS_MasterFileTable() {
  // Do nothing
}

NTFS_MasterFileTable::NTFS_MasterFileTable(BYTE* sector) {
  NTFS_ExtendedBIOSParameterBlock EBPB(sector);
  NTFS_BIOSParameterBlock BPB(sector);

  _startingSector = EBPB.MFTClusterNumber() * BPB.bytesPerSector();
}

void NTFS_MasterFileTable::readSector(BYTE* sector) { _readSector(sector); }
unsigned int NTFS_MasterFileTable::startingSector() { return _startingSector; }
std::string NTFS_MasterFileTable::toString() { return _toString(); }

void NTFS_MasterFileTable::setMFTB(NTFS_MasterFileTableBlock MFTB) {
  _MFTB = MFTB;
}

/// <summary>
/// Read starting sector from BPB and EBPB
/// </summary>
/// <param name="sector"></param>
void NTFS_MasterFileTable::_readSector(BYTE* sector) {
  
}

std::string NTFS_MasterFileTable::_toString() {
  std::stringstream ss;

  return ss.str();
}