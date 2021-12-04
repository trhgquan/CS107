#include "syscall.h"

int main() {
	int n;
	PrintString("Moi thay nhap thu 1 so nguyen bat ki:");
	n = ReadInt();	
	PrintChar('\n');
	PrintString("So thay vua nhap la: ");
	PrintInt(n);
	PrintChar('\n');
	Halt();
}
