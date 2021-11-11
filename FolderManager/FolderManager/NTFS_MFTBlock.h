#pragma once
#ifndef MFT_BLOCK
#define MFT_BLOCK

#include"IBlock.h"

class NTFS_MasterFileTableBlock : public IBlock {
private:
  const unsigned int FILE_FLAG = 0x01;
  const unsigned int FODLER_FLAG = 0x02;

  std::string _fileName;
  unsigned int _fileSize;
  unsigned int _fileSizeAllocated;
  unsigned int _flags;

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
