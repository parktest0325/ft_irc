#include "../include/Server.h"
#include "../include/Client.h"

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <map>

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
	ClientsCleanup();
	closesocket(mServerFd);
	WSACleanup();
}

void Server::Listen(const std::string _port)
{
	mPort = _port;

	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(stoi(mPort));
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
		PrintError("AcceptClient", "accept()");
		return -1;
	}

	mClients.insert(std::make_pair(clientFd, new Client(clientFd)));
	return clientFd;
}

void Server::ClientsCleanup()
{
	for (std::map<SOCKET, Client*>::iterator it = mClients.begin();
		it != mClients.end(); ++it)
	{
		delete it->second;
	}
}

void Server::Execute(SOCKET _sender, std::string& _msg)
{
	SOCKET target;
	for (std::map<SOCKET, Client*>::iterator it = mClients.begin();
		it != mClients.end(); ++it)
	{
		target = it->second->GetFd();
		if (target != _sender)
			send(target, _msg.c_str(), _msg.size(), NULL);
	}
}

void Server::Run(const std::string _password)
{
	mPassword = _password;

	FD_SET fds, copyFds;
	SOCKET curFd, acceptFd;

	FD_ZERO(&fds);
	FD_SET(mServerFd, &fds);
	while (true)
	{
		copyFds = fds;
		int fdCount = select(0, &copyFds, nullptr, nullptr, nullptr);
		for (int i = 0; i < fdCount; i++)
		{	
			// copyFds의 fd_array에 [0] 부터 변경이 감지된 소켓만 저장된다.
			curFd = copyFds.fd_array[i];
			if (curFd == mServerFd)
			{
				acceptFd = AcceptClient();
				if (acceptFd >= 0)
					FD_SET(acceptFd, &fds);
			}
			else
			{
				// 개행이 입력될때까지 데이터 추가
				int recvSize;
				recvSize = recv(curFd, mMsgBuffer, Server::MsgBufferSize, NULL);

				//do
				//{
				//	recvSize = recv(curFd, mMsgBuffer, Server::MsgBufferSize, NULL);
				//} while (recvSize == Server::MsgBufferSize);

				mMsgQueue[curFd].assign(mMsgBuffer);

				if (recvSize < 0)
					PrintError("recvSize", " < 0");	// Error;
				else if (recvSize == 0)
					PrintError("recvSize", " == 0");	// Ctrl+C
				else
					Execute(curFd, mMsgQueue[curFd]);

				
			}
		}
	}
}


void Server::Error(const std::string _curMethod, const std::string _position)
{
	Release();
	PrintError(_curMethod, _position);
	return;
}

void Server::PrintError(const std::string _curMethod, const std::string _position) const
{
	std::cerr << "[Fail] Server:: " << _curMethod << " => " << _position << std::endl;
}

