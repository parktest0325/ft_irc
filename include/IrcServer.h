#pragma once
#include "Server.h"
#include <string>
#include <map>
#include <vector>

class Channel;
class ClientInfo;

class IrcServer :
    public Server
{
public:
	void SetPassword(const std::string _password) { mPassword = _password; }

	virtual void Execute(SOCKET _sender, std::string& _msg) override;

private:
	void AddChannel();
	void RemoveChannel(const std::string _name);
	
	void AddClientInfo();
	void RemoveClientInfo(SOCKET _fd);

	std::vector<std::string> Parsing(const std::string& _msg);

private:
	std::string mPassword;
	std::map<std::string, Channel*> mChannels;
	std::map<SOCKET, ClientInfo*> mClientInfos;
};

