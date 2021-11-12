#include "SDET.h"

//Getter
int SDET::clusterNumber() { return _clusterNumber; }

SDET::SDET(): RDET()
{
	//do nothing
}

SDET::SDET(FAT* fat, int clusterNumber) : RDET(fat, clusterNumber)
{
	_clusterNumber = clusterNumber;
}


SDET::~SDET()
{
	//do nothing
}
