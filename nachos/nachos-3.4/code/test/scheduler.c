#include "syscall.h"

int main() {
	int pingPID, pongPID;
	int pingExitCode, pongExitCode;
	PrintString("Ping-Pong test starting...\n\n");
	pingPID = Exec("./test/ping");
	pongPID = Exec("./test/pong");

	pingExitCode = Join(pingPID);
	pongExitCode = Join(pongPID);

	//Exit(pingExitCode);
	//Exit(pongExitCode);

	PrintString("\nFinish Ping-Pong test\n");
}

