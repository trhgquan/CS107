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

/*System call handler for each system call protoypes*/
using namespace SCHandler {

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

			if ('-' == buffer[offset]) {

				//we will not accept 2 or more '-'
				if (isNegative) 
				{
					return 0;
				}

				isNegative = true;


			}
			else if ('.' == buffer[offset]) {
				if (isReal || isNegative) 
				{
					return 0;
				}
				
				//buffer like: "  -.12321 " => not a number
				if (offset > 0 && '-' == buffer[offset - 1])
				{
					return 0;
				}

				//only get the natural part if the number is real number
				isReal = true;
				coeff = 1;
				value = 0;

			}
			else if (' ' == buffer[offset]) {
				
				//if all characters from buffer[0 : offset] is not ' ' => 0
				while (offset > 0) {
					--offset;
					if (' ' != buffer[offset])
					{
						return 0;
					}

				}

			}
			else if ('0' <= buffer[offset] && buffer[offset] <= '9') {
				value += (coeff * (buffer[offset] - '0'));
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
		if (0 == number) return "0";

		//check if number is negative
		bool isNegative = (number < 0 ? true : false);

		//Get number as absolute value
		if (isNegative) number *= -1;

		//number of digits of number
		length = 1;	

		//copy of number
		int temp_number = number;

		//get number of digits
		while (temp_number > 0) {
			temp_number /= 10;
			++length;
		}

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
		while (temp_number > 0) {
			int digit = temp_number % 10;
			temp_number /= 10;
			buffer[i] = digit;
			--i;
		}

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
			delete[] buffer;
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
		machine->SystemToUser(
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
