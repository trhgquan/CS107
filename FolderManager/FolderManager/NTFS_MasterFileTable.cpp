#include "NTFS_MasterFileTable.h"
#include "NTFS_MFTBlock.h"
#include "NTFS_VolumeBootRecord.h"
#include "SectorReader.h"
#include "Utility.h"
#include <sstream>
#include <vector>

NTFS_MasterFileTable::NTFS_MasterFileTable() {
  // Do nothing
}

NTFS_MasterFileTable::~NTFS_MasterFileTable() {
  // Do nothing
}

NTFS_MasterFileTable::NTFS_MasterFileTable(NTFS_VolumeBootRecord VBR) {
  _startingSector = VBR.EBPB().MFTClusterNumber() * VBR.BPB()->sectorPerCluster();
}

void NTFS_MasterFileTable::readSector(BYTE* sector) { _readSector(sector); }
void NTFS_MasterFileTable::setMFTB(const NTFS_MasterFileTableBlock& MFTB) { _MFTB.push_back(MFTB); }
unsigned int NTFS_MasterFileTable::startingSector() { return _startingSector; }
std::string NTFS_MasterFileTable::toString() { return _toString(); }
std::vector<NTFS_MasterFileTableBlock> NTFS_MasterFileTable::MFTB() { return _MFTB; }

/// <summary>
/// Read starting sector from BPB and EBPB
/// </summary>
/// <param name="sector"></param>
void NTFS_MasterFileTable::_readSector(BYTE* sector) {
  NTFS_MasterFileTableBlock MFTB(sector);

  setMFTB(MFTB);
}

std::string NTFS_MasterFileTable::_toString() {
  std::stringstream ss;

  return ss.str();
}