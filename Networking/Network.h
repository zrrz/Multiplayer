#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <iostream>

class Network() {
	int Send(SOCKET* socket, char msg[]);

	char* Recv(SOCKET* socket);
	
	void RecvLoop();

	void Close();

	SOCKET ListenSocket;

	SOCKET ConnectSockets[MAXCONNECTIONS];
	int numconnections;

	addrinfo *result;
	addrinfo hints;
	addrinfo *ptr;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen;

	Network() {
		for (int i = 0; i < MAXCONNECTIONS; i++) {
			ConnectSockets[i] = INVALID_SOCKET;
		}
		numconnections = 0;

	}

	void Connect(void* arg) {
		Netowkr* net = (Network*)arg;
		net->Connect();
	}
};

#endif