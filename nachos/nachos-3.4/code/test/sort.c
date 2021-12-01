/* sort.c 
 *    Test program to sort a large number of integers.
 *
 *    Intention is to stress virtual memory system.
 *
 *    Ideally, we could read the unsorted array off of the file system,
 *	and store the result back to the file system!
 */

#include "syscall.h"

#define TYPE_ASCENDING 1
#define TYPE_DESCENDING 2

#define MAX_SIZE 100;
int A[MAX_SIZE + 1];	/* size of physical memory; with code, we'll run out of space!*/

bool compare(int a, int b, int compareType) {
	if (TYPE_ASCENDING == compareType) {
		if (a < b)
		{
			return true;
		}
		return false;
	}
	
	//Descending
	if (a < b) 
	{
		return false;
	}

	return true;
}

int main() {

	//Input type of sort
	int type;
	PrintString("- Moi thay nhap kieu sort:\n");
	PrintString("\t+ 1: Tang dan | 2: Giam dan\n");
	type = ReadInt();

	while (type != TYPE_ASCENDING && type != TYPE_DESCENDING) {
		PrintString("\t+ Khong hop le: Chi duoc chon gia tri 1 hoac 2\n");
		PrintString("- Moi thay nhap lai kieu sort: ");
		type = ReadInt();
	}

	//Input size of an array
	int n;
	PrintString("- Moi thay nhap so luong phan tu cua mang can sort: ");
	n = ReadInt();

	//Valid check for size of an array
	while (n < 0) {
		PrintString("\t+ Khong hop le: So luong phan tu phai la so duong!\n");
		PrintString("- Moi thay nhap lai: ");
		n = ReadInt();
	}



	//Input array
	int i;
	for (i = 0; i < n; ++i) {
		PrintString("a[");
		PrintInt(i);
		PrintString("] = ");
		a[i] = ReadInt();
	}

	//Bubble sort
	int j, temp;
	for (i = 0; i < n - 1; ++i) {
		for (j = i + 1; j < n; ++j) {
			if (compare(a[i], a[j], type)){
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}

	}


	//output
	PrintString("- Mang sau khi da sap xep bang bubble sort la:\n");
	for (i = 0; i < n; ++i) {
		PrintInt(a[i]);
		PrintChar(' ');
	}
	PrintChar('\n');
	
	Halt();
}
