#include <thread>
#include "server.hpp"

int main()
{
	Server server(3000);
	server.start();
	return (0);
}

