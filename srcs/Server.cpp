#include "../include/Server.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

void Server::Init()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		return Error("Init", "WSAStartup()");
	}

	mServerFd = socket(AF_INET, SOCK_STREAM, 0);
	if (mServerFd == INVALID_SOCKET)
	{
		return Error("Init", "socket()");
	}
}

void Server::Release()
{
	closesocket(mServerFd);
	WSACleanup();
}


void Server::Listen()
{
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(mPort);
	serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;

	if (bind(mServerFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		return Error("Listen", "bind()");
	}

	if (listen(mServerFd, Server::MaxConn) == SOCKET_ERROR)
	{
		return Error("Listen", "listen()");
	}
}

SOCKET Server::AcceptClient()
{
	SOCKET clientFd;
	sockaddr_in	clientAddr;
	int clientAddrSize = sizeof(clientAddr);

	clientFd = accept(mServerFd, (SOCKADDR*)&clientAddr, &clientAddrSize);
	if (clientFd == INVALID_SOCKET)
	{

	}

	return clientFd;
}

void Server::Run()
{
	FD_SET fds, copyFds;
	SOCKET curFd;

	FD_ZERO(&fds);
	FD_SET(mServerFd, &fds);
	while (true)
	{
		copyFds = fds;
		int fdCount = select(0, &copyFds, nullptr, nullptr, nullptr);
		for (int i = 0; i < fdCount; i++)
		{
			curFd = copyFds.fd_array[i];
			if (curFd == mServerFd)
			{
				FD_SET(AcceptClient(), &fds);
			}
			else
			{
				// Command Ã³¸®
			}
		}
	}
}

void Server::Error(const std::string _curMethod, const std::string _position)
{
	Release();
	std::cerr << "[Fail] Server:: " << _curMethod << " => " << _position << std::endl;
	return;
}

