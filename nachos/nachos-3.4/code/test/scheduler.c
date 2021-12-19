#include "syscall.h"

int main() {
	int pingPID, pongPID;
	PrintString("Ping-Pong test starting...\n\n");
	pingPID = Exec("ping");
	pongPID = Exec("pong");

	Join(pingPID);
	Join(pongPID);
}