#include "../include/Client.h"

Client::~Client()
{
	closesocket(mFd);
}

SOCKET Client::GetFd() const
{
	return mFd;
}
