#include "syscall.h"

int main() {

	PrintString("Moi thay nhap thu 1 so nguyen bat ki:");
	int n = ReadInt();
	PrintChar('\n');
	PrintString("So thay vua nhap la: ");
	PrintInt(n);
	PrintChar('\n');
	Halt();
}