#include "NetworkManager.h"
#include <iostream>

using namespace std;

NetworkManager* NetworkManager::instance = nullptr;

NetworkManager::NetworkManager()
{
	TCPSocketIn = INVALID_SOCKET;
	TCPSocketOut[0] = INVALID_SOCKET;

	TCPoutAddr = { 0 };
	TCPinAddr = { 0 };
}

NetworkManager::~NetworkManager()
{

}

void NetworkManager::Init()
{
	cout << "NetworkManager::Init() called." << endl;

	WSADATA lpWSAData;
	int error = WSAStartup(MAKEWORD(2, 2), &lpWSAData);
	if (error != 0)
	{
		cout << "WSAData failed with error: " << WSAGetLastError() << endl;
	}
}

void NetworkManager::CreateTCPSockets()
{
	cout << "NetworkManager::CreateTCPSockets()" << endl;

	TCPSocketIn = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (TCPSocketIn == INVALID_SOCKET)
	{

		cout << "Failed to create in socket." << endl;
		Shutdown();
		if (closesocket(TCPSocketIn) != 0)
		{
			cout << "[ERROR] closing TCPSocket in." << endl;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		TCPSocketOut[i] = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (TCPSocketOut[i] == INVALID_SOCKET)
		{
			cout << "Failed to create out socket " << i << "." << endl;
			Shutdown();
			if (closesocket(TCPSocketOut[i]) != 0)
			{
				cout << "[ERROR] closing TCPSocket out " << i << "." << endl;
			}
		}
	}
}

void NetworkManager::BindTCP()
{
	sin_port = 8889;

	TCPinAddr.sin_family = AF_INET; // IPv4
	TCPinAddr.sin_port = htons(sin_port);
	TCPinAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	int bindError = bind(TCPSocketIn, reinterpret_cast<SOCKADDR*>(&TCPinAddr), sizeof(TCPinAddr));

	if (bindError == SOCKET_ERROR)
	{
		cout << "[ERROR] binding TCP in Socket " << endl;

		Shutdown();
	}
}

void NetworkManager::ListenTCP()
{
	listen(TCPSocketIn, SOMAXCONN);
}

void NetworkManager::ConnectTCP()
{
	sin_port = 8889;

	TCPoutAddr.sin_family = AF_INET; // IPv4
	TCPoutAddr.sin_port = htons(sin_port);

	string IP;
	cout << "Please enter an IP to connect to: " << endl;
	cin >> IP;

	inet_pton(AF_INET, IP.c_str(), &TCPoutAddr.sin_addr);

	int connectStatus = connect(TCPSocketOut[numConnections], reinterpret_cast<sockaddr*>(&TCPoutAddr), sizeof(TCPoutAddr));

	if (connectStatus == SOCKET_ERROR)
	{
		cout << "[ERROR] clients Connection through TCP failed." << endl;
		Shutdown();
	}
	numConnections++;
	unsigned long unblocking = 1;
	ioctlsocket(TCPSocketOut[numConnections - 1], FIONBIO, &unblocking);
}

void NetworkManager::AcceptConnectionsTCP(bool& playerFound)
{
	int clientSize = sizeof(TCPoutAddr);

	TCPSocketOut[numConnections] = accept(TCPSocketIn, reinterpret_cast<sockaddr*>(&TCPoutAddr), &clientSize);

	if (TCPSocketOut[numConnections] != INVALID_SOCKET)
	{
		char ipConnected[32];
		inet_ntop(AF_INET, &TCPoutAddr.sin_addr, ipConnected, 32);
		cout << "User with IP: " << ipConnected << " just connected." << endl;
		numConnections++;
		playerFound = true;
	}

	unsigned long unblocking = 1;
	ioctlsocket(TCPSocketOut[numConnections - 1], FIONBIO, &unblocking);
	ioctlsocket(TCPSocketIn, FIONBIO, &unblocking);
}

void NetworkManager::SendDataTCP(const char* message)
{
	for (int i = 0; i < numConnections; i++)
	{
		int totalBytes = send(TCPSocketOut[i], message, strlen(message) + 1, 0);

		if (totalBytes == SOCKET_ERROR)
		{
			int error = WSAGetLastError();
			if (error == WSAEWOULDBLOCK)
			{
				cout << "sent: " << totalBytes << " of data." << endl;
			}
			else
			{
				cout << "[ERROR] TCP Send Failed." << endl;
				Shutdown();
			}
		}

		cout << "sent: " << totalBytes << "of data." << endl;
	}
}

int NetworkManager::ReceiveDataTCP(char* message)
{
	int bytesReceived;
	for (int i = 0; i < numConnections; i++)
	{
		bytesReceived = recv(TCPSocketOut[i], message, MAX_MESSAGE, 0);

		if (bytesReceived == SOCKET_ERROR)
		{
			int error = WSAGetLastError();
			if (error != WSAEWOULDBLOCK)
			{
				cout << "[ERROR] error receiving from TCP Socket " << i << "." << endl;
				Shutdown();
			}
		}
		if (bytesReceived > 0)
		{
			return bytesReceived;

		}
		else if (bytesReceived == SOCKET_ERROR)
		{
			int error = WSAGetLastError();
			if (error != WSAEWOULDBLOCK)
			{
				cout << "[ERROR] error receiving from TCP Socket " << i << "." << endl;
				Shutdown();
			}
		}
	}
	return bytesReceived;
}

void NetworkManager::Shutdown()
{
	cout << "NetworkManager::Shutdown()" << endl;
	int error = WSAGetLastError();
	if (error != 0)
	{
		cout << "WSAData failed with error: " << error << endl;
	}

	WSACleanup();

	for (int i = 0; i < numConnections; i++)
	{
		if (TCPSocketOut[i] != INVALID_SOCKET)
		{
			if (closesocket(TCPSocketOut[i]) != 0)
			{
				cout << "[ERROR] closing TCPSocket out" << i + 1 << endl;
			}
		}
	}

	if (TCPSocketIn != INVALID_SOCKET)
	{
		if (closesocket(TCPSocketIn) != 0)
		{
			cout << "[ERROR] closing TCPSocket in" << endl;
		}
	}
}