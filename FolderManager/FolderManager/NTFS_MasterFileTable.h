#pragma once
#ifndef NTFS_MFT
#define NTFS_MFT

#include "IBlock.h"
#include "NTFS_MFTBlock.h"
#include "NTFS_VolumeBootRecord.h"
#include <vector>

class NTFS_MasterFileTable : public IBlock {
private:
  unsigned int _startingSector;
  std::vector<NTFS_MasterFileTableBlock> _MFTB;

private:
  std::string _toString();
  void _readSector(BYTE*);

public:
  NTFS_MasterFileTable();
  ~NTFS_MasterFileTable();
  NTFS_MasterFileTable(NTFS_VolumeBootRecord);

public:
  std::string toString();
  void readSector(BYTE*);
  
  unsigned int startingSector();
  
  void setMFTB(const NTFS_MasterFileTableBlock&);
  std::vector<NTFS_MasterFileTableBlock> MFTB();

};

#endif