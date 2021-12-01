#include "syscall.h"

int main() {
	PrintString("- Cac thanh vien trong nhom:\n");
	PrintString("\t+ 19120338 - Tran Hoang Quan\n");
	PrintString("\t+ 19120383 - Huynh Tan Tho\n");
	PrintString("\t+ 19120407 - Lam Hai Trieu\n");
	PrintString("\t+ 19120426 - Phan Dang Diem Uyen\n");
	PrintString("\t+ 19120469 - Su Nhat Dang\n");

	PrintString("- Ngoai 2 chuong trinh ascii va sort, ");
	PrintString("bon em con lam them 3 chuong trinh de test 6 system call tuong ung, do la:\n");
	PrintString("\t+ ioInt: test PrintInt/ReadInt\n");
	PrintString("\t+ ioChar: test PrintChar/ReadChar\n");
	PrintString("\t+ ioString: test PrintString/ReadString\n");
	PrintString("- Ca 3 chuong trinh nay deu nam trong folder ./test/\n\n");

	PrintString("- Gioi thieu chuong trinh ascci:\n");
	PrintString("Chuong trinh ascii cho phep xuat ra gia tri Dec cua 1 ki tu va ki tu trong pham vi tu [32; 127], ");
	PrintString("vi day la vung ma console co the xuat ra ki tu ascci co the nhin thay duoc\n\n");

	PrintString("- Gioi thieu chuong trinh sort:\n");
	PrintString("Chuong trinh sort cho phep nguoi dung nhap kieu sort (tang/giam), so luong phan tu (<=100) va ");
	PrintString("tung phan tu trong mang can sort. Chuong trinh se xuat ra man hinh ket qua cua mang sau khi sort\n");

	Halt();
}