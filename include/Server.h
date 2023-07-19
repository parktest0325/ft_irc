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
	Server()
		: mServerFd(0), mPort({})
	{
		Init();
	};
	virtual ~Server()
	{
		Release();
	};

	void Listen(const std::string _port);
	void Run();

	void DeleteClient(SOCKET _curFd);

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
	std::string		mPort;

	std::map<SOCKET, Client*>		mClients;	// 연결 끊길때를 생각해서 map으로 구현
	std::map<SOCKET, std::string>	mMsgQueue;	// 메시지가 개행까지 들어올때까지 저장
												// 개행이 여러개 들어올 수 있지만 그건 파싱때 처리

	char			mMsgBuffer[MsgBufferSize];
};

