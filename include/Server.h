#pragma once

#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <list>

class Client;

class Server
{
public:
	static constexpr int MaxConn = 10;

public:
	Server(const std::string _port, const std::string _password)
		: mServerFd(0), mPort(stoi(_port)), mPassword(_password)
	{
		Init();
	};
	~Server()
	{
		Release();
	};

	void Listen();
	void Run();

private:
	void Init();
	void Release();
	SOCKET AcceptClient();

	void Error(const std::string _curMethod, const std::string _position);

private:
	SOCKET				mServerFd;

	int					mPort;
	std::string			mPassword;

	std::list<Client*>	mClients;
};

