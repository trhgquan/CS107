#pragma once
#ifndef _FAT32_FORMAT_H_
#define _FAT32_FORMAT_H_

#include "AbstractFormat.h"
#include "FAT32_VolumeBootRecord.h"
#include "RDET.h"


class FAT32_Format: public AbstractFormat {
private:
	FAT32_VolumeBootRecord* _vbr = nullptr;
	FAT* _fat = nullptr;
	RDET* _rdet = nullptr;

protected:	//protected utilities
	void _run(LPCWSTR) override;
	void _removeMemory();

public:		//API
	void run(LPCWSTR) override;

public:
	FAT32_Format();
	FAT32_Format(LPCWSTR);
	~FAT32_Format() override;
};


#endif // !_FAT32_FORMAT_H_



