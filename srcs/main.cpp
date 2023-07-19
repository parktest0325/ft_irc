#include <iostream>
#include "../include/IrcServer.h"

int main(int argc, char* argv[])
{
	std::string port, password;
	if (argc > 3)
		return 0;
	port = argc < 2 ? "4321" : argv[1];
	password = argc < 3 ? "4321" : argv[2];

	IrcServer s;
	s.Listen(port);
	s.Run();
	return 0;
}