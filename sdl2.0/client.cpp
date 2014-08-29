//#define WIN32_LEAN_AND_MEAN
//
//#include <windows.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include<process.h>
//#include<iostream>
//
//// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
//#pragma comment (lib, "Ws2_32.lib")
//#pragma comment (lib, "Mswsock.lib")
//#pragma comment (lib, "AdvApi32.lib")
//
//using namespace std;
//#define DEFAULT_BUFLEN 512
//#define DEFAULT_PORT "27017"
//
//SOCKET ConnectSocket = INVALID_SOCKET;
//char buffer[512] = { 0 };
//
//void RecvLoop(void* param) {
//	SOCKET *socket = (SOCKET*)param;
//	int in_msg;
//
//	while (true) {
//		in_msg = recv(*socket, buffer, 512, 0);
//		if (!in_msg)
//			break;
//		cout << endl << "\In:    " << buffer << endl;
//		//printf("%s \n", buffer);
//	}
//}
//
//int main(int argc, char **argv) {
//	WSADATA wsaData;
//
//	struct addrinfo *result = NULL,
//		*ptr = NULL,
//		hints;
//	char *sendbuf = "Hiya";
//	char recvbuf[DEFAULT_BUFLEN];
//	int iResult;
//	int recvbuflen = DEFAULT_BUFLEN;
//	char ipaddr[] = "127.0.0.1";
//
//	// Validate the parameters
//	if (argc != 2) {
//		printf("usage: %s server-name\n", argv[0]);
//		//return 1;
//	}
//
//	// Initialize Winsock
//	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
//	if (iResult != 0) {
//		printf("WSAStartup failed with error: %d\n", iResult);
//		return 1;
//	}
//
//	ZeroMemory(&hints, sizeof(hints));
//	hints.ai_family = AF_UNSPEC;
//	hints.ai_socktype = SOCK_STREAM;
//	hints.ai_protocol = IPPROTO_TCP;
//
//	// Resolve the server address and port
//	iResult = getaddrinfo(ipaddr, DEFAULT_PORT, &hints, &result);
//	if (iResult != 0) {
//		printf("getaddrinfo failed with error: %d\n", iResult);
//		WSACleanup();
//		return 2;
//	}
//
//	// Attempt to connect to an address until one succeeds
//	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
//
//		// Create a SOCKET for connecting to server
//		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
//		if (ConnectSocket == INVALID_SOCKET) {
//			printf("socket failed with error: %ld\n", WSAGetLastError());
//			WSACleanup();
//			return 3;
//		}
//
//		// Connect to server.
//		printf("connecting...");
//		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
//		if (iResult == SOCKET_ERROR) {
//			closesocket(ConnectSocket);
//			ConnectSocket = INVALID_SOCKET;
//			continue;
//		}
//		break;
//	}
//
//	if (ConnectSocket == INVALID_SOCKET) {
//		printf("Unable to connect to server!\n");
//		WSACleanup();
//		return 4;
//	}
//
//	// Send an initial buffer
//	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
//	if (iResult == SOCKET_ERROR) {
//		printf("send failed with error: %d\n", WSAGetLastError());
//		closesocket(ConnectSocket);
//		WSACleanup();
//		return 5;
//	}
//
//	char out_msg[512];
//
//	printf("%s Bytes Sent: %ld\n", sendbuf, iResult);
//	//printf("%d Recieved\n", rec);
//	int r = WSAGetLastError();
//
//	HANDLE thread = (HANDLE)_beginthread(RecvLoop, 0, (void*)&ConnectSocket);
//	do {
//		cout << "Out: ";
//		cin.getline(recvbuf, 512);
//		iResult = send(ConnectSocket, recvbuf, (int)strlen(recvbuf) + 1, 0);
//		//printf("%s \n", buffer);
//		if (iResult == -1)
//			break;
//	} while (iResult != NULL);
//
//	// cleanup
//	closesocket(ConnectSocket);
//	WSACleanup();
//
//	system("Pause");
//	return 0;
//}