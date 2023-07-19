#pragma once

class IrcServer;

class IrcCommandHandler
{
public:
	IrcCommandHandler(IrcServer* _server) : mServer(_server) {};

public:
	void Execute();

private:
	IrcServer* mServer;
};

// 명령 디스패처
//typedef void (IRCServer::* CommandFunction)(std::string);
//std::map<std::string, CommandFunction> commandMap;
//void IRCServer::processCommand(std::string command, std::string arguments) {
//	CommandFunction function = commandMap[command];
//	(this->*function)(arguments);
//}
// command로 mChannels와 mClientInfos를 넘겨야함 

