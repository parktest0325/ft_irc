#include <sstream>
#include "../include/IrcServer.h"
#include <iostream>

void IrcServer::Execute(SOCKET _sender, std::string& _msg)
{
	std::vector<std::string> cmds = Parsing(_msg);

	for (std::string cmd : cmds)
	{
		Server::Execute(_sender, cmd);
	}
}

void IrcServer::AddChannel()
{
}

void IrcServer::RemoveChannel(const std::string _name)
{
}

void IrcServer::AddClientInfo()
{
}

void IrcServer::RemoveClientInfo(SOCKET _fd)
{
}

std::vector<std::string> IrcServer::Parsing(const std::string& _msg)
{
	std::vector<std::string> ret;
	std::stringstream ss(_msg);
	std::string tmp;

	// \r \n 전부 제거해준다. 
	while (ss >> tmp)
		ret.push_back(tmp);
	return ret;
}
