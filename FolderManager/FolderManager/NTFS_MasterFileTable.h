#pragma once
#ifndef NTFS_MFT
#define NTFS_MFT

#include "IBlock.h"
#include "NTFS_MFTBlock.h"
#include "SectorReader.h"

class NTFS_MasterFileTable : public IBlock {
private:
  unsigned int _startingSector;
  NTFS_MasterFileTableBlock _MFTB;

private:
  std::string _toString();
  void _readSector(BYTE*);

public:
  NTFS_MasterFileTable();
  ~NTFS_MasterFileTable();
  NTFS_MasterFileTable(BYTE*);

public:
  std::string toString();
  void readSector(BYTE*);
  unsigned int startingSector();
  void setMFTB(NTFS_MasterFileTableBlock);
};

#endif