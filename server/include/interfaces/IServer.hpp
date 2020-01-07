#ifndef _ISERVER_H
#define _ISERVER_H

#include <vector>
#include "interfaces/ISockets.hpp"

class IServer
{
public:
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual ~IServer(){};

private:
	struct Client
	{
		int sckt;
//		sockaddr_in addr;
	};
	virtual void setRunningState(bool) = 0;
	virtual void configureSelect() = 0;
	virtual void handleClients() = 0;
	virtual void handleCommands(fd_set &setReads, fd_set &setWrite, fd_set &setErrors) = 0;
	std::vector<Client> clients;
};
#endif
