#include "Network.h"
#include "SDL_thread.h"
#include "Manager.h"

// Manager* Network::manager = NULL;

int Network::Init() {
	manager = Manager::instance;
	if (isServer) {
		//mem.numConnect = 1;
		WSADATA wsaData;
		int iResult;

		struct addrinfo *result = NULL;
		struct addrinfo hints;

		int iSendResult;
		char recvbuf[DEFAULT_BUFLEN];
		int recvbuflen = DEFAULT_BUFLEN;

		// Initialize Winsock
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			printf("WSAStartup failed with error: %d\n", iResult);
			return 1;
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		// Resolve the server address and port
		iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
			return 1;
		}

		// Create a SOCKET for connecting to server
		mem.ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (mem.ListenSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			return 1;
		}

		// Setup the TCP listening socket
		iResult = bind(mem.ListenSocket, result->ai_addr, (int)result->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			printf("bind failed with error: %d\n", WSAGetLastError());
			freeaddrinfo(result);
			closesocket(mem.ListenSocket);
			WSACleanup();
			return 1;
		}

		mem.numConnect = 0;
		HANDLE thread = (HANDLE)_beginthread(&Network::Static_ConnectLoop, 0, this);

		int r = WSAGetLastError();

		/*HANDLE thread = (HANDLE)*/_beginthread(&Network::Static_RecvLoop, 0, this);
		/*do {
			cout << "Out:   ";
			cin.getline(recvbuf, 512);
			for (int i = 0; i < mem.numConnect; i++)
			{
				iResult = send(mem.ClientSocket[i], recvbuf, (int)strlen(recvbuf) + 1, 0);
			}

			if (iResult == -1)
				break;
		} while (iResult != NULL);*/
	} else {
		WSADATA wsaData;

		struct addrinfo *result = NULL,
			*ptr = NULL,
			hints;
		char *sendbuf = "Connected!";
		char recvbuf[DEFAULT_BUFLEN];
		int iResult;
		int recvbuflen = DEFAULT_BUFLEN;
		char ipaddr[] = "127.0.0.1";

		//// Validate the parameters
		//if (argc != 2) {
		//	printf("usage: %s server-name\n", argv[0]);
		//	//return 1;
		//}

		// Initialize Winsock
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			printf("WSAStartup failed with error: %d\n", iResult);
			return 1;
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		// Resolve the server address and port
		iResult = getaddrinfo(ipaddr, DEFAULT_PORT, &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
			return 2;
		}

		// Attempt to connect to an address until one succeeds
		for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

			// Create a SOCKET for connecting to server
			ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
			if (ConnectSocket == INVALID_SOCKET) {
				printf("socket failed with error: %ld\n", WSAGetLastError());
				WSACleanup();
				return 3;
			}

			// Connect to server.
			printf("connecting...");
			iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
			if (iResult == SOCKET_ERROR) {
				closesocket(ConnectSocket);
				ConnectSocket = INVALID_SOCKET;
				continue;
			}
			break;
		}

		if (ConnectSocket == INVALID_SOCKET) {
			printf("Unable to connect to server!\n");
			WSACleanup();
			return 4;
		}

		// Send an initial buffer
		iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 5;
		}

		//char out_msg[512];

		printf("%s Bytes Sent: %ld\n", sendbuf, iResult);
		//printf("%d Recieved\n", rec);
		int r = WSAGetLastError();

		//SDL_Thread* thread = SDL_CreateThread(Static_RecvLoop, "RecvLoop", (void*)&ConnectSocket);

		HANDLE thread = (HANDLE)_beginthread(&Network::Static_RecvLoop, 0, this);
	/*	do {
			cout << "Out: ";
			cin.getline(recvbuf, 512);
			iResult = send(ConnectSocket, recvbuf, (int)strlen(recvbuf) + 1, 0);
			printf("%s \n", buffer);
			if (iResult == -1)
				break;
		} while (iResult != NULL);*/
	}
}

void Network::Send(char* msg) {
	int iResult;
	for (int i = 0; i < mem.numConnect; i++)
	{
		iResult = send(mem.ClientSocket[i], msg, (int)strlen(msg) + 1, 0);
	}
}

void Network::RecvLoop() {
	SOCKET* socket;// = (SOCKET*)param;
	int in_msg;

	if (isServer) {
		socket = mem.ClientSocket;
		fd_set set;
		timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = 100;
		int result = 0;
		int temp = 0;

		while (true) {
			for (int i = 0; i < mem.numConnect; i++) {
				FD_ZERO(&set);
				FD_SET(mem.ClientSocket[i], &set);
				result = select(0, &set, NULL, NULL, &timeout);

				if (result > 0) {
					in_msg = recv(mem.ClientSocket[i], inBuffer, 512, 0);
					temp = i;

					if (!in_msg)
						break;

					cout << "\In:    " << inBuffer << endl;

					if (!HandleMessage(inBuffer))
						break;

					for (int i = 0; i < mem.numConnect; i++) {
						if (i != temp)
							send(mem.ClientSocket[i], inBuffer, (int)strlen(inBuffer) + 1, 0);
					}
				}
				else if (result < 0) {
					cout << "No CONNECTION" << i << endl;
				}
			}
		}
	}
	else {
		socket = &ConnectSocket;
		while (true) {
			in_msg = recv(*socket, inBuffer, 512, 0);
			if (!in_msg)
				break;
			cout << endl << "\In:    " << inBuffer << endl;

			HandleMessage(inBuffer);
		}
	}
}

void Network::ConnectLoop() {
	SOCKET* socket = &mem.ListenSocket;

	int iResult;
	printf("listening...");
	while (true) {
		iResult = listen(mem.ListenSocket, SOMAXCONN);
		if (iResult == SOCKET_ERROR) {
			printf("listen failed with error: %d\n", WSAGetLastError());
			closesocket(mem.ListenSocket);
			WSACleanup();
			//return 1;
		}

		// Accept a client socket

		mem.ClientSocket[mem.numConnect] = accept(mem.ListenSocket, NULL, NULL);

		if (mem.ClientSocket[mem.numConnect] == INVALID_SOCKET) {
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(*socket);
			WSACleanup();
			//return 1;
		}
		mem.numConnect++;
	}
	//return 0;
}

void Network::Static_RecvLoop(void* param) {
	static_cast<Network*>(param)->RecvLoop();
}

void Network::Static_ConnectLoop(void* param) {
	static_cast<Network*>(param)->ConnectLoop();
}

bool Network::HandleMessage(char* msg) {
//	if (msg == "left")
//		manager.player.MoveLeft();
	return 1;
}

void Network::Close() {
	if (isServer) {
		for (int i = 0; i < 3; i++) {
			closesocket(mem.ClientSocket[i]);
		}
	}
	else {
		closesocket(ConnectSocket);	
	}

	WSACleanup();
}