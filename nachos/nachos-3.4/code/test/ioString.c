#include "syscall.h"
#define MAX_BUFFER_LENGTH 254

int main() {

	PrintString("Moi thay nhap thu 1 chuoi bat ki:");
	char* buffer = new char[MAX_BUFFER_LENGTH];
	ReadString(buffer, MAX_BUFFER_LENGTH);
	PrintChar('\n');
	PrintString("Chuoi nhap la: ");
	PrintString(buffer);
	PrintChar('\n');
	delete buffer;
	Halt();
}