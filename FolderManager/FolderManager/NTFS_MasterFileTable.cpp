#include "NTFS_MasterFileTable.h"
#include "NTFS_ExtendedBIOSParameterBlock.h"
#include "NTFS_BIOSParameterBlock.h"
#include <sstream>

NTFS_MasterFileTable::NTFS_MasterFileTable() {
  _startingSector = 0;
}

NTFS_MasterFileTable::~NTFS_MasterFileTable() {
  // Do nothing
}

NTFS_MasterFileTable::NTFS_MasterFileTable(BYTE* sector) {
  _readSector(sector);
}

void NTFS_MasterFileTable::readSector(BYTE* sector) { _readSector(sector); }
std::string NTFS_MasterFileTable::toString() { return _toString(); }

/// <summary>
/// Read starting sector from BPB and EBPB
/// </summary>
/// <param name="sector"></param>
void NTFS_MasterFileTable::_readSector(BYTE* sector) {
  NTFS_ExtendedBIOSParameterBlock EBPB(sector);
  NTFS_BIOSParameterBlock BPB(sector);

  _startingSector = EBPB.MFTClusterNumber() * BPB.bytesPerSector();
}

std::string NTFS_MasterFileTable::_toString() {
  std::stringstream ss;

  ss << "Starting at sector " << _startingSector;

  return ss.str();
}