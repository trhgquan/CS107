#pragma once
#ifndef MFT_BLOCK
#define MFT_BLOCK

#include"IBlock.h"

class NTFS_MasterFileTableBlock : public IBlock {
private:
  std::string _signature;

private:
  void _readSector(BYTE*);

public:
  NTFS_MasterFileTableBlock();
  ~NTFS_MasterFileTableBlock();
  NTFS_MasterFileTableBlock(BYTE*&);

public:
  std::string toString();
  void readSector(BYTE*);
};

#endif
