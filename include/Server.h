#pragma once

#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

class Server
{
public:
	Server(const std::string _port, const std::string _password)
		: port(stoi(_port)), password(_password), listenQueueSize(10), socket(0)
	{
		Init();
	};
	~Server()
	{
		Release();
	};

	void Init();
	void Release();
	void Listen();
	void Run();
private:

	int	port;
	int listenQueueSize;
	std::string password;
	SOCKET sock;

	



};

