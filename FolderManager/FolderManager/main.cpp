#include "SectorReader.h"
#include "Utility.h"

int main() {
	// NTFS
	//SectorReader reader(L"\\\\.\\D:", 0);

	//int val = 0;

	//for (int i = 0; i < DEFAULT_BUFFER_SIZE; ++i) {
	//	//printf("%d ", *(reader.sector() + i));
	//	printf("%x ", *(reader.sector() + i));
	//}

	//printf("%d\n", val);

	// Marng => Hex?
	std::vector<int> a = { 0x3f, 0x00, 0x00, 0x00};

	std::cout << Utility::little_endian(a);

	system("PAUSE");
	return 0;
}