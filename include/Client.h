#pragma once

#include <WinSock2.h>
#include <string>

class Client
{
public:
	Client(SOCKET _fd) : mFd(_fd) {};
	virtual ~Client();

	SOCKET GetFd() const;

private:
	const SOCKET mFd;
};

