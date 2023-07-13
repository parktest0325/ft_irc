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

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		return Error("Init", "socket()");
	}
}

void Server::Release()
{
	closesocket(sock);
	WSACleanup();
}

void Server::Listen()
{
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;

	if (bind(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		return Error("Listen", "bind()");
	}

	if (listen(sock, Server::MaxConn) == SOCKET_ERROR)
	{
		return Error("Listen", "listen()");
	}
}

void Server::Run()
{
}

void Server::Error(const std::string cur_method, const std::string position)
{
	Release();
	std::cerr << "[Fail] Server:: " << cur_method << " => " << position << std::endl;
	return;
}

