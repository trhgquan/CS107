#pragma once
#ifndef _NTFS_FORMAT_H_
#define _NTFS_FORMAT_H_

#include "NTFS_VolumeBootRecord.h"
#include "AbstractFormat.h"

class NTFS_Format: public AbstractFormat {
private: 
	NTFS_VolumeBootRecord* _vbr = nullptr;

protected:	//protected utilities
	void _read(LPCWSTR) override;
	void _removeMemory();

public:
	NTFS_Format();
	NTFS_Format(LPCWSTR);
	~NTFS_Format() override;
};


#endif // !_NTFS_FORMAT_H_



