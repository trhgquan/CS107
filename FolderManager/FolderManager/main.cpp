#include "SectorReader.h"
#include "PartitionBootSector.h"
#include "Utility.h"
#include <iostream>

int main() {

	//Read buffer from drive //D:
	SectorReader reader(L"\\\\.\\D:", 0 * DEFAULT_BUFFER_SIZE);

	//Get the index of VBR sector (0-indexing)
	int VBRSectorIndex = Utility::valueInLittleEndian(reader.sector(), 0x01BE + 8, 4);
	printf("%d\n", VBRSectorIndex);

	//Get the sector from the VBRSectorIndex-sector
	reader.readSector(L"\\\\.\\D:", VBRSectorIndex*DEFAULT_BUFFER_SIZE);

	//Load the sector to parse data
	PartitionBootSector PBS(reader.sector());

	//Print data
	std::cout << PBS.toString() << "\n";

	system("PAUSE");
	return 0;
}