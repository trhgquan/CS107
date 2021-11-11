#pragma once
#ifndef NTFS_MFT
#define NTFS_MFT

#include "IBlock.h"

class NTFS_MasterFileTable : public IBlock {
private:
  unsigned int _startingSector;

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
};

#endif