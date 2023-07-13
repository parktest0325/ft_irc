#pragma once

#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

class Server
{
public:
	Server(const std::string _port, const std::string _password)
		: port(stoi(_port)), password(_password), sock(0)
	{
		// 积己磊 抗寇贸府
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
	void Error(const std::string cur_method, const std::string position);

private:
	static constexpr int MaxConn = 10;

	SOCKET			sock;

	int				port;
	std::string		password;
};

