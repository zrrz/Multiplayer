//#undef UNICODE
//
//#define WIN32_LEAN_AND_MEAN
//
//#include <windows.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <process.h>
////#include <Windows.h>
//#include <iostream>
//// Need to link with Ws2_32.lib
//#pragma comment (lib, "Ws2_32.lib")
//// #pragma comment (lib, "Mswsock.lib")
//using namespace std;
//
//#define DEFAULT_BUFLEN 512
//#define DEFAULT_PORT "27017"
//
//char buffer[512]={0};
//
//struct sharedMem
//{
//		SOCKET ListenSocket;// = INVALID_SOCKET;
//		SOCKET ClientSocket[3];// = INVALID_SOCKET;
//		int numConnect;
//} app;
//
//void RecvLoop(void* param) {
//	SOCKET *socket = (SOCKET*)param;
//	int in_msg;
//	fd_set thing;
//	timeval timeout;
//	timeout.tv_sec = 0;
//	timeout.tv_usec = 100;
//	int result = 0;
//	int temp = 0;
//
//	while(true) {
//		for(int i =0; i < app.numConnect; i++) {
//			FD_ZERO(&thing);
//			FD_SET(app.ClientSocket[i],&thing);
//			result = select(0, &thing, NULL, NULL, &timeout);
//
//			if(result > 0) {
//				in_msg = recv(app.ClientSocket[i],buffer,512,0);
//				temp = i;
//
//				if(!in_msg)
//					break;
//
//				cout<< "\In:    "<< buffer << endl;
//				for(int i =0; i < app.numConnect; i++) {
//					if (i != temp)
//						send(app.ClientSocket[i],buffer, (int)strlen(buffer)+1, 0 );
//				}
//			} else if( result < 0 ) {
//				cout << "No CONNECTION" << i<< endl;
//			}
//		}
//	}
//}
//
//void ConnectLoop(void* param) {
//	SOCKET *socket = (SOCKET*)param;
//
//	int iResult;
//	printf("listening...");
//	while(true) {
//		iResult = listen(app.ListenSocket, SOMAXCONN);
//		if (iResult == SOCKET_ERROR) {
//			printf("listen failed with error: %d\n", WSAGetLastError());
//			closesocket(app.ListenSocket);
//			WSACleanup();
//			//return 1;
//		}
//
//		// Accept a client socket
//	
//		app.ClientSocket[app.numConnect] = accept(app.ListenSocket, NULL, NULL);
//	
//		if (app.ClientSocket[app.numConnect] == INVALID_SOCKET) {
//			printf("accept failed with error: %d\n", WSAGetLastError());
//			closesocket(*socket);
//			WSACleanup();
//			//return 1;
//		}
//		app.numConnect++;
//	}
//	//return 0;
//}
//
//int main(void) {
//    WSADATA wsaData;
//    int iResult;
//
//    struct addrinfo *result = NULL;
//    struct addrinfo hints;
//
//    int iSendResult;
//    char recvbuf[DEFAULT_BUFLEN];
//    int recvbuflen = DEFAULT_BUFLEN;
//
//    // Initialize Winsock
//    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
//    if (iResult != 0) {
//        printf("WSAStartup failed with error: %d\n", iResult);
//        return 1;
//    }
//
//    ZeroMemory(&hints, sizeof(hints));
//    hints.ai_family = AF_INET;
//    hints.ai_socktype = SOCK_STREAM;
//    hints.ai_protocol = IPPROTO_TCP;
//    hints.ai_flags = AI_PASSIVE;
//
//    // Resolve the server address and port
//    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
//    if ( iResult != 0 ) {
//        printf("getaddrinfo failed with error: %d\n", iResult);
//        WSACleanup();
//        return 1;
//    }
//
//    // Create a SOCKET for connecting to server
//	app.ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
//    if (app.ListenSocket == INVALID_SOCKET) {
//        printf("socket failed with error: %ld\n", WSAGetLastError());
//        freeaddrinfo(result);
//        WSACleanup();
//        return 1;
//    }
//
//    // Setup the TCP listening socket
//    iResult = bind( app.ListenSocket, result->ai_addr, (int)result->ai_addrlen);
//    if (iResult == SOCKET_ERROR) {
//        printf("bind failed with error: %d\n", WSAGetLastError());
//        freeaddrinfo(result);
//		closesocket(app.ListenSocket);
//        WSACleanup();
//        return 1;
//    }
//
//	app.numConnect = 0;
//	HANDLE thread = (HANDLE)_beginthread(ConnectLoop,0,(void*)app.ListenSocket);
//
//	int r = WSAGetLastError();
//
//	/*HANDLE thread = (HANDLE)*/_beginthread(RecvLoop, 0, (void*)app.ClientSocket);
//	do {
//		cout<< "Out:   ";
//		cin.getline(recvbuf, 512);
//		for(int i =0; i < app.numConnect; i++)
//		{
//			iResult  = send(app.ClientSocket[i],recvbuf, (int)strlen(recvbuf)+1, 0 );
//		}
//		
//		if (iResult == -1)
//			break;
//	} while (iResult != NULL);
// 
//    // cleanup
//	for(int i =0; i < 3; i ++) {
//		closesocket(app.ClientSocket[i]);
//	}
//
//    WSACleanup();
//
//    return 0;
//}