#include "syscall.h"
#define MAX_ASCII_VISIBLE 126
#define MIN_ASCII_VISIBLE 32

int main() {
	int i;
	PrintString("Sau day la bang ma ASCII cho cac ki tu co the nhin thay duoc (la cac ki tu nam trong khoang [32, 126])\n");
	for (i = MIN_ASCII_VISIBLE; i <= MAX_ASCII_VISIBLE; ++i) {
		PrintInt(i);
		PrintChar(':');
		PrintChar((char)i);
		PrintChar('\n');
	}

	Halt();
}
