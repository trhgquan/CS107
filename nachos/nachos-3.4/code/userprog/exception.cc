// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"

#define MAX_BUFFER_LENGTH 255
#define R2 2
#define R4 4
#define R5 5
#define R6 6

/*System call handler for each system call protoypes*/
namespace SCHandler {

	/*
		Input:	- An array of character to check if it show up as a number (char *) (input)
				- Number of characters in the array (int) (input)
				
		Output:	Return the value of natural part if the array is an number
				Return 0 if the array is not a number
	*/

	int StringToNumber(char* buffer, int numBytes) {

		bool isNegative = false;	//check if negative number
		bool isReal = false;		//check if real number

									//start offset = last charcter offset
		int offset = numBytes - 1;

		//ignore all " " at the ends
		while (offset >= 0 && ' ' == buffer[offset]) { --offset; }

		//if the buffer is contain all ' ' => 0
		if (-1 == offset) { return 0; }

		//meet the first '.' => '123.000' still a integer, '123.125' would return '123'
		if ('.' == buffer[offset]) { isReal = true; --offset; }

		//if the buffer is liked ".   " => 0
		if (-1 == offset) { return 0; }

		//we would never meet '-' of negative number if we traversal from the end
		if ('-' == buffer[offset]) { return 0; }

		int i;
		int coeff = 1;
		int value = 0;
		for (i = offset; i >= 0; --i) {

			if ('-' == buffer[i]) {

				//we will not accept 2 or more '-'
				if (isNegative)
				{
					return 0;
				}

				isNegative = true;


			}
			else if ('.' == buffer[i]) {

				if (isReal || isNegative) 
				{
					return 0;
				}

				//buffer like: "  -.12321 " => not a number
				if (i > 0 && '-' == buffer[i - 1])
				{
					return 0;
				}

				//only get the natural part if the number is real number
				isReal = true;
				coeff = 1;
				value = 0;

			}
			else if (' ' == buffer[i]) {
				
				//if all characters from buffer[0 : i] is not ' ' => 0

				while (i > 0) {
					--i;
					if (' ' != buffer[i])
					{
						return 0;
					}

				}

			}
			else if ('0' <= buffer[i] && buffer[i] <= '9') {
				value += (coeff * (buffer[i] - '0'));
				coeff *= 10;
			}
			else {
				return 0;
			}


		}

		return (isNegative ? -1 * value : value);
	}
	

	/*
	Input:	- A number to convert to char* (int) (input)
			- An integer reference to store the length of character string after convert (int) (output)

	Output:	Return the string after converting, if cannot allocate memory, return NULL
	*/

	char* NumberToString(int number, int& length) {
		if (0 == number) {
			length = 1;
			return "0";
		}
		//check if number is negative
		bool isNegative = (number < 0 ? true : false);

		//Get number as absolute value
		if (isNegative) number *= -1;

		//number of digits of number
		length = 0;	

		//copy of number
		int temp_number = number;

		//get number of digits
		do {
			temp_number /= 10;
			++length;
		}while (temp_number > 0);

		//length += 1 if negative (space for '-')
		length += (isNegative ? 1 : 0);
		
		//+1 for null-terminated, +1 for sure
		char* buffer = new char[length + 1 + 1];

		//cannot allocated because of something => error
		if (!buffer) return NULL;

		//add '-' if number is negative
		if (isNegative)
		{
			buffer[0] = '-';
		}

		//reuse temp_number as copy of number
		temp_number = number;

		//iterator
		int i = length - 1;	

		//Get absolute value
		do {
			int digit = temp_number % 10;
			temp_number /= 10;
			buffer[i] = (digit + '0');
			--i;
		}while (i >= 0 && temp_number > 0);

		//add null-terminated
		buffer[length] = NULL;

		return buffer;
	}

	/************************/
	/*System call defination*/
	/************************/
	int ReadInt() {
		char buffer[MAX_BUFFER_LENGTH + 1];
		int numberOfReadChar = synchConsole->Read(buffer, MAX_BUFFER_LENGTH);
		int value = StringToNumber(buffer, numberOfReadChar);
		machine->WriteRegister(R2, value);
		machine->IncreasePC();
		return value;
	}

	void PrintInt(int number) {
		int length = 0;	//number of digits in number
		char* buffer = NumberToString(number, length);

		//if (NULL == buffer) => cannot allocate to buffer
		if (buffer) {
			synchConsole->Write(buffer, length);
			
			//We don't need to delete while number = 0, because we havent't new it yet
			if (0 != number)
			{
				delete[] buffer;
			}
		}
		else 
		{
			DEBUG('a', "ERROR: Doesn't have enough memory to allocate\n");	
		}

		
		machine->IncreasePC();
		
	}

	char ReadChar() {
		char buffer[MAX_BUFFER_LENGTH + 1];

		//get buffer from console
		int numberOfReadChar = synchConsole->Read(buffer, MAX_BUFFER_LENGTH);

		//init for readChar
		char readChar = NULL;

		if (0 == numberOfReadChar) {
			DEBUG('a', "ERROR: Empty input for ReadChar()\n");
			machine->WriteRegister(R2, 0);	//Get NULL for output
		}
		else if (-1 == numberOfReadChar) {
			DEBUG('a', "ERROR: Console error\n");
			machine->WriteRegister(R2, 0);	//Get NULL for output
		}
		else if (-2 == numberOfReadChar) {
			DEBUG('a', "ERROR: EOF Console\n");
			machine->WriteRegister(R2, 0);	//Get NULL for output
		} 

		else {

			//if user type a string => get only the first character
			readChar = buffer[0];
			machine->WriteRegister(R2, readChar);
		}
		machine->IncreasePC();
		return readChar;
	}

	void PrintChar(char character) {
		synchConsole->Write(&character, 1);
		machine->IncreasePC();
	}

	void ReadString(char* buffer, int length) {
		synchConsole->Read(buffer, length);
		machine->System2User(
			machine->ReadRegister(R4),
			length,
			buffer);
		machine->IncreasePC();
		delete[] buffer;
	}

	void PrintString(char* buffer) {
		int length = 0;

		while (length < MAX_BUFFER_LENGTH && NULL != buffer[length])
		{
			++length;
		}

		if (MAX_BUFFER_LENGTH == length)
		{
			//get max length
			DEBUG('a', "Error: Number of characters in string must not over 254 character");
		}
		else
		{
			//+1 for null-terminated
			synchConsole->Write(buffer, length + 1);
		}	

		machine->IncreasePC();
		delete buffer;
	}


	/*
	Input: reg4 -filename (string)
	Output:
	Purpose: process the event SC_Create of System call
	*/

	int doSC_Create()
	{
		int virtAddr;
		char* filename;

		//  printf("\n SC_Create call...");
		//printf("\n Reading virtual address of file name.");
		DEBUG(dbgFile, "\n SC_Create call ...");
		DEBUG(dbgFile, "\n Reading virtual address of filename");

		// check for exception
		virtAddr = machine->ReadRegister(R4);
		DEBUG(dbgFile, "\n Reading filename.");
		filename = machine->User2System(virtAddr, MAX_BUFFER_LENGTH + 1);
		if (filename == NULL)
		{
			printf("\n Not enough memory in system");
			DEBUG(dbgFile, "\n Not enough memory in system");
			machine->WriteRegister(R2, -1);
			delete filename;
			return -1;
		}

		if (strlen(filename) == 0 || (strlen(filename) >= MAX_BUFFER_LENGTH + 1))
		{
			printf("\n Too many characters in filename: %s", filename);
			DEBUG(dbgFile, "\n Too many characters in filename");
			machine->WriteRegister(R2, -1);
			delete filename;
			return -1;
		}

		//printf("\n Finish reading filename.");
		//printf("\n File name: '%s'",filename);
		DEBUG(dbgFile, "\n Finish reading filename.");
		//DEBUG(dbgFile,"\n File name : '"<<filename<<"'");

		// Create file with size = 0
		if (!fileSystem->Create(filename, 0))
		{
			printf("\n Error create file '%s'", filename);
			delete filename;
			machine->WriteRegister(R2, -1);
			delete filename;
			return -1;
		}
		//printf("\n Create file '%s' success",filename);

		machine->WriteRegister(R2, 0);

		machine->IncreasePC();
		delete filename;
		return 0;
	}

	/*
	Input:
	Output:
	Purpose: End thread , because exit() was called
	*/
	int doSC_Exit()
	{
		printf("\n\n Calling SC_Exit.");
		DEBUG(dbgFile, "\n\n Calling SC_Exit.");

		// avoid harry
		IntStatus oldLevel = interrupt->SetLevel(IntOff);

		int exitStatus;
		//ProcessHashData *processData;

		exitStatus = machine->ReadRegister(R4);

		// if process exited with error, print error
		if (exitStatus != 0)
			printf("\nProcess %s exited with error level %d", currentThread->getName(), exitStatus);

		//  currentThread->Finish();
		(void)interrupt->SetLevel(oldLevel);
		interrupt->Halt();
		machine->IncreasePC();
		return 0;
	}


	/*
	Input: OpenfileID = reg4
	Output: 0- success , -1 - fail
	Purpose: do close file
	*/
	int doSC_Close()
	{
		int id = machine->ReadRegister(R4);
		if (id < 0 || id >= currentThread->fTab->GetMax())
		{
			printf("\n CloseError: Unexpected file id: %d", id);
			return -1;
		}
		if (!currentThread->fTab->IsExist(id)) {
			printf("\n CloseError: closing file id %d is not opened", id);
			return -1;
		}

		//currentThread->
		currentThread->fTab->fdClose(id);
		machine->IncreasePC();
		return 0;
	}

	/*
	Input: offset = reg4, OpenFileID = reg5
	Output: currentOffset, or -1 - fail
	Purpose: do seek the pointer of a file. If seek to offset -1 mean SEEK_END
	*/
	int doSC_Seek()
	{
		int id = machine->ReadRegister(R5);
		if (id < 0 || id >= currentThread->fTab->GetMax())
		{
			printf("\n SC_SeekError: Unexpected file id: %d", id);
			return -1;
		}
		if (!currentThread->fTab->IsExist(id)) {
			printf("\n SC_SeekError: seeking file id %d is not opened", id);
			return -1;
		}

		int offset = machine->ReadRegister(R4);
		currentThread->fTab->fdSeek(offset, id);
		machine->IncreasePC();
		return 0;
	}

	/*
	Input: User space address = reg4, buffer size = reg5, OpenfileID = reg6
	Output: -1: error
	numbytes were read
	Purpose: do read from file or console
	*/
	int doSC_Read()
	{
		//  printf("\n Calling SC_Read.");
		int virtAddr = machine->ReadRegister(R4);
		int size = machine->ReadRegister(R5);
		int id = machine->ReadRegister(R6);

		if (size <= 0)
		{
			printf("\nSC_ReadError: unexpected buffer size: %d", size);
			return -1;
		}

		if (id < 0 || id >= currentThread->fTab->GetMax())
		{
			printf("\n ReadError: Unexpected file id: %d", id);
			return -1;
		}
		if (!currentThread->fTab->IsExist(id)) {
			printf("\n ReadError: reading file id %d is not opened", id);
			return -1;
		}

		int rs = currentThread->fTab->fdRead(virtAddr, size, id);

		machine->WriteRegister(R2, rs);
		machine->IncreasePC();
		return rs;
	}

	/*
	Input: User space address = reg4, buffer size= reg5, OpenFileID = reg6
	Output: = -1 - error
	or = numbytes were writen
	Purpose: do write to file or console
	*/
	int doSC_Write()
	{
		//  printf("\n Calling SC_Write.");
		int virtAddr = machine->ReadRegister(R4);
		int size = machine->ReadRegister(R5);
		int id = machine->ReadRegister(R6);

		if (size < 0)
		{
			printf("\nSC_WriteError: unexpected buffer size: %d", size);
			return -1;
		}
		else if (size == 0)
			return 0;

		if (id < 0 || id >= currentThread->fTab->GetMax())
		{
			printf("\n WriteError: Unexpected file id: %d", id);
			return -1;
		}
		if (!currentThread->fTab->IsExist(id)) {
			printf("\n WriteError: writing file id %d is not opened", id);
			return -1;
		}

		int rs = currentThread->fTab->fdWrite(virtAddr, size, id);

		machine->WriteRegister(R2, rs);
		machine->IncreasePC();
		return rs;
	}

	/*
	Input: file type (reg5)
	0 - standard file
	1 - read only
	2 - encrypted

	Output:  -1 - error
	OpenFileID -success

	Purpose: do Open a file
	*/
	int doSC_Open()
	{
		//  printf("\n Calling SC_Open.");
		int virtAddr = machine->ReadRegister(R4);
		int type = machine->ReadRegister(R5);

		if (type < 0 || type > 2)
		{
			printf("\n SC_OpenError: unexpected file type: %d", type);
			return -1;
		}

		int id = currentThread->fTab->FindFreeSlot();
		if (id < 0)
		{
			printf("\n SC_OpenError: No free slot.");
			return -1;
		}

		char *filename = machine->User2System(virtAddr, MAX_BUFFER_LENGTH + 1);

		if (filename == NULL)
		{
			printf("\n Not enough memory in system");
			DEBUG(dbgFile, "\n Not enough memory in system");
			machine->WriteRegister(R2, -1);
			delete filename;
			return -1;
		}

		if (strlen(filename) == 0 || (strlen(filename) >= MAX_BUFFER_LENGTH + 1))
		{
			printf("\n Too many characters in filename: %s", filename);
			DEBUG(dbgFile, "\n Too many characters in filename");
			machine->WriteRegister(R2, -1);
			delete filename;
			return -1;
		}

		OpenFile* of = fileSystem->Open(filename);

		if (of == NULL) {
			printf("\n Error opening file:  %s", filename);
			DEBUG(dbgFile, "\n Error opening file.");
			machine->WriteRegister(2, -1);
			delete filename;
			return -1;
		}

		int rs = currentThread->fTab->fdOpen(virtAddr, type, id, of);

		machine->WriteRegister(R2, rs);
		machine->IncreasePC();
		return rs;
	}

	int doSC_Exec() {

		int virtAddr = machine->ReadRegister(R4);
		char* processName = NULL;
		processName = User2System(virtAddr, MAX_BUFFER_LENGTH + 1);

		if (!processName) {
			printf("\n Error opening process");
			machine->WriteRegister(R2, -1);
			return -1;
		}

		machine->WriteRegister(R2, pTab->ExecUpdate(processName));

		if (processName) 
		{
			delete processName;
		}
		machine->IncreasePC();
		return 0;
	}
}

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------



void
ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);

    switch (which) {
    case NoException:
        return;

    case SyscallException:
        // Syscall exceptions goes here.
	switch (type) {
	case SC_Halt:
	    DEBUG('a', "Shutdown, initiated by user program.\n");
	    interrupt->Halt();
	    break;	
	case SC_ReadInt:
		SCHandler::ReadInt();
		break;
	case SC_PrintInt:
		SCHandler::PrintInt(
			machine->ReadRegister(R4));
		break;
	case SC_ReadChar:
		SCHandler::ReadChar();
		break;
	case SC_PrintChar:
		SCHandler::PrintChar(
			machine->ReadRegister(R4));
		break;
	case SC_ReadString:
		SCHandler::ReadString(
			machine->User2System(
				machine->ReadRegister(R4),
				machine->ReadRegister(R5)),
			machine->ReadRegister(R5));

		break;
	case SC_PrintString:
		SCHandler::PrintString(
			machine->User2System(
				machine->ReadRegister(R4),
				MAX_BUFFER_LENGTH));
		
		break;
	case SC_Create:
		SCHandler::doSC_Create();
		break;
	case SC_Exit:
		SCHandler::doSC_Exit();
		break;
	case SC_Close:
		SCHandler::doSC_Close();
		break;
	case SC_Seek:
		SCHandler::doSC_Seek();
		break;
	case SC_Read:
		SCHandler::doSC_Read();
		break;
	case SC_Write:
		SCHandler::doSC_Write();
		break;
	case SC_Open:
		SCHandler::doSC_Open();
		break;
	case SC_Exec:
		SCHandler::doSC_Exec();
		break;
	default:
	    printf("Unexpected user mode exception %d %d\n", which, type);
	    ASSERT(FALSE);
	}
	break;

    // Catching all exceptions
    case PageFaultException:
    case ReadOnlyException:
    case BusErrorException:
    case AddressErrorException:
    case OverflowException:
    case IllegalInstrException:
	DEBUG('a', "Exception triggered");
	printf("Exception triggered: %d\n", which);
	ASSERT(FALSE);
	interrupt->Halt();
	break;
    }
}
