#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <process.h>

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


// need to link with ws2_32.lib, mswsock.lib, and advapi32.lib
#pragma comment (lib, "ws2_32.lib")
#pragma comment (lib, "mswsock.lib")
#pragma comment (lib, "advapi32.lib")

using namespace std;

WSADATA wsaData;
int iResult;

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27017"

SOCKET ConnectSocket = INVALID_SOCKET;
SOCKET ListenSocket = INVALID_SOCKET;

struct addrinfo *result = NULL;
struct addrinfo hints;
struct addrinfo *ptr = NULL;

int iSendResult;
char recvbuf[DEFAULT_BUFLEN];
int recvbuflen = DEFAULT_BUFLEN;

int main() {
	char msg[100] = "Sorry I ate your sandwhich, but it was delish!!";
	
	//HANDLE thread = (HANDLE)_beginthread(threadfunc, 0, msg);
	//WaitForSingleObject(thread, INFINITE);

	cout << "recv: " << msg << endl;

	//for (int i = 0; i < 10; i++) {
	//	for (char l = 'a'; l <= 'z'; l++) {
	//		cout << '\t' << l << endl;
	//		Sleep(250);
	//	}
	//}

	char ipaddr[] = "10.229.22.183";

	SetupServer(DEFAULT_PORT);
	SetupClient(DEFAULT_PORT, ipaddr);
	return 0;
}

void SetupServer(char* port) {

}

void SetupClient(char* port, char* ip) {

}

char* Recv(SOCKET* socket) {
	return NULL;
}

void RecvLoop(void* param) {
	SOCKET *socket = (SOCKET*)param;
	char* in_msg;
	while (1) {
		in_msg = Recv(&ConnectSocket);
		if (!in_msg)
			break;
		cout << "\aIn: " << in_msg << endl;
	}
}

int Send(SOCKET* socket, char msg[]) {
	return NULL;
}

//struct Package {
//	SOCKET* socket;
//	char msg[512];
//};

int Connect() {
	// Accept a client socket
	ConnectSocket = accept(ListenSocket, NULL, NULL);
	if (ConnectSocket == INVALID_SOCKET) {
	    printf("accept failed with error: %d\n", WSAGetLastError());
	    closesocket(ListenSocket);
	    WSACleanup();
	    return -1;
	}
	printf("Connected!!\n");
	// No longer need server socket
	closesocket(ListenSocket);
}

void Server(char port[]) {
	char out_msg[DEFAULT_BUFLEN] = { 0 };
	int result;

	SetupServer(port);
	if (Connect() == -1)
		cout << "Error: Faioled to connect";

	/*Package pack;
	pack.socket = &ConnectSocket;*/

	_beginthread(RecvLoop, 0, (void*)&ConnectSocket);
	do {
		//get msg, send out
		cout << "Out: ";
		cin.getline(out_msg, 512);
		result = Send(&ConnectSocket, out_msg);
		if (result == -1)
			break;
	} while (result != -1);
}

void Client(char port[], char ip[]) {
	char out_msg[DEFAULT_BUFLEN] = { 0 };
	char* in_msg;
	int result = 0;

	SetupClient(port, ip);

	_beginthread(RecvLoop, 0, &ConnectSocket);

	do {

	} while (result != -1);
}

void Close() {

}