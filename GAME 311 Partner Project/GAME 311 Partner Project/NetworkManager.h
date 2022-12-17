#pragma once
#pragma comment(lib,"ws2_32.lib")
#include <iostream>
#include <WS2tcpip.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WinSock2.h>

class NetworkManager
{
public:

	static NetworkManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new NetworkManager();
		}
		return instance;
	}

	void Init();
	void CreateTCPSockets();
	void BindTCP();
	void ListenTCP();
	void ConnectTCP();
	void AcceptConnectionsTCP(bool& playerFound);
	void SendDataTCP(const char* message);
	int ReceiveDataTCP(char* Message);
	void Shutdown();

	int GetNumConnections() { return numConnections; }

	static const int MAX_MESSAGE = 1500;
	int sin_port = 0;

private:

	NetworkManager();
	~NetworkManager();

	SOCKET TCPSocketIn;
	SOCKET TCPSocketOut[4];

	SOCKADDR_IN TCPoutAddr;
	SOCKADDR_IN TCPinAddr;

	int numConnections = 0;

	static NetworkManager* instance;

};