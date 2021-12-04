#include "syscall.h"
#define MAX_BUFFER_LENGTH 254

int main() {
	char* buffer[MAX_BUFFER_LENGTH - 1];
	PrintString("Moi thay nhap thu 1 chuoi bat ki:");
	ReadString(buffer, MAX_BUFFER_LENGTH);
	PrintChar('\n');
	PrintString("Chuoi nhap la: ");
	PrintString(buffer);
	PrintChar('\n');
	Halt();
}
