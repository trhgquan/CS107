#pragma once
#ifndef _SDET_H_
#define _SDET_H_

#include "RDET.h"

class SDET: public RDET {
private:
	int _clusterNumber;

public://getter
	int clusterNumber();

public:
	SDET();
	SDET(FAT*, int);
	~SDET() override;
};


#endif // !_SDET_H_



