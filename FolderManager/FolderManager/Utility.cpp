#include "Utility.h"
#include <sstream>

int Utility::valueInLittleEndian(BYTE* sector, int offset, int length) {
	int res = 0;
	int coeff = 1;
	int endPos = offset + length;
	for (int i = offset; i < endPos; ++i) {
		res += (int)sector[i] * coeff;
		coeff *= HEX*HEX;
	}

	return res;
}

std::string Utility::getStringFromSector(BYTE* sector, int offset, int length) {
	std::stringstream builder;
	int endPos = offset + length;
	for (int i = offset; i < endPos; ++i) {
		builder << (unsigned char)sector[i];
	}
	return builder.str();
}