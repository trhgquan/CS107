#include "Utility.h"

/// <summary>
/// Reverse a little endian bytes, calculate it in decimal
/// </summary>
/// <param name="bytes">std::vector<int></param>
/// <returns>int</returns>
int Utility::little_endian(const std::vector<int>& bytes) {
	int coeff = 1, res = 0;

	for (int i = 0; i < (size_t)bytes.size(); ++i) {
		res += bytes[i] * coeff;
		coeff *= 16;
	}

	return res;
}