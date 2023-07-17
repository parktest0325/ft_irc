#include <iostream>
#include "../include/Server.h"

int main(int argc, char* argv[])
{
	std::string port, password;
	if (argc > 3)
		return 0;
	port = argc < 2 ? "4321" : argv[1];
	password = argc < 3 ? "4321" : argv[2];

	Server s(port, password);
	s.Listen();
	s.Run();
	return 0;
}