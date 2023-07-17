#pragma once

#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <map>

class Client;

class Server
{
public:
	static constexpr size_t MaxConn = 10;
	static constexpr size_t	MsgBufferSize = 1024;

public:
	Server(const std::string _port, const std::string _password)
		: mServerFd(0), mPort(stoi(_port)), mPassword(_password)
	{
		Init();
	};
	virtual ~Server()
	{
		Release();
	};

	void Listen();
	void Run();

protected:
	virtual void Execute(SOCKET _sender, std::string& _msg);

private:
	void Init();
	void Release();
	SOCKET AcceptClient();
	void ClientsCleanup();

	void Error(const std::string _curMethod, const std::string _position);
	void PrintError(const std::string _curMethod, const std::string _position) const;

private:
	SOCKET			mServerFd;
	int				mPort;
	std::string		mPassword;

	std::map<SOCKET, Client*>		mClients;	// ���� ���涧�� �����ؼ� map���� ����
	std::map<SOCKET, std::string>	mMsgQueue;	// �޽����� ������� ���ö����� ����
												// ������ ������ ���� �� ������ �װ� �Ľ̶� ó��

	char			mMsgBuffer[MsgBufferSize];
};

