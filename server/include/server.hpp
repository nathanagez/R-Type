#ifndef _SERVER_H
#define _SERVER_H
#include "interfaces/IServer.hpp"
#include "interfaces/IPackets.hpp"
#include "sockets.hpp"

class Server : public IServer
{
public:
	Server(int port = 3000);
	void start();
	void stop();
	~Server();

private:
	struct Client
	{
		int sckt;
		std::string username;
		sockaddr_in addr;
	};
	struct Lobby
	{
		int lobbyState;//0 no launched   1 launched
		std::string lobbyId;
		std::vector<Client> clientsLobby;
		Client createdBy;
	};
	int m_lobbyId;
	int m_port;
	bool m_runningState;
	int selectCount;
	void setRunningState(bool);
	void configureSelect();
	void handleClients();
	void handleCommands(fd_set &setReads, fd_set &setWrite, fd_set &setErrors);
	std::shared_ptr<ISockets> m_serverSocket;
	std::vector<Client> clients;
	std::vector<Lobby> lobbies;
};

#endif
