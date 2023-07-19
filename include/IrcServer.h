#pragma once
#include "Server.h"
#include <string>
#include <map>
#include <vector>
#include "IrcCommandHandler.h"

class Channel;
class ClientInfo;

class IrcServer :
    public Server
{
public:
	IrcServer() : mPassword({}), mChannels({}), mClientInfos({}), mCommand(this) {};

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

	IrcCommandHandler mCommand;

	friend class IrcCommandHandler;
};

// 명령 디스패처
//typedef void (IRCServer::* CommandFunction)(std::string);
//std::map<std::string, CommandFunction> commandMap;
//void IRCServer::processCommand(std::string command, std::string arguments) {
//	CommandFunction function = commandMap[command];
//	(this->*function)(arguments);
//}
// command로 mChannels와 mClientInfos를 넘겨야함 

