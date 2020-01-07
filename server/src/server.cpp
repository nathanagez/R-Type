#include <thread>
#include <vector>
#include <memory>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include "server.hpp"
#include "serialize.hpp"
#include "game.hpp"

std::vector<std::thread> ths;

Server::Server(int port) : m_lobbyId(0), m_port(port), m_serverSocket(new Sockets(m_port, 4, "TCP")) {}

void Server::configureSelect()
{
	fd_set set;
	timeval timeout = {};
	FD_ZERO(&set);
	FD_SET(this->m_serverSocket->getSocket(), &set);
	selectCount = select(static_cast<int>(this->m_serverSocket->getSocket()) + 1, &set, nullptr, nullptr, &timeout);
}

void Server::start()
{
	this->setRunningState(true);
	while (this->m_runningState)
	{
		this->configureSelect();
		if (this->selectCount == -1)
		{
			std::cerr << "Erreur select pour accept : " << std::endl;
			break;
		}
		if (this->selectCount > 0)
		{
			sockaddr_in from = {0};
			socklen_t addrlen = sizeof(from);
			int newClientSocket = this->m_serverSocket->accept(from, addrlen);
			if (newClientSocket != -1)
			{
				Client newClient{newClientSocket, "", from};
				const std::string clientAddress = this->m_serverSocket->getAddress(from);
				getsockname(this->m_serverSocket->getSocket(), (sockaddr *)&from, &addrlen);
				const unsigned short clientPort = ntohs(from.sin_port);
				std::cout << "Connexion de " << clientAddress.c_str() << ":" << clientPort << std::endl;
				this->clients.push_back(newClient);
			}
		}
		this->handleClients();
	}
}

void Server::handleClients()
{
	if (!clients.empty())
	{
		fd_set setReads;
		fd_set setWrite;
		fd_set setErrors;
		FD_ZERO(&setReads);
		FD_ZERO(&setWrite);
		FD_ZERO(&setErrors);
		int highestFd = 0;
		timeval timeout = {0};
		int selectResult = 0;

		for (auto &client : clients)
		{
			FD_SET(static_cast<int>(client.sckt), &setReads);
			FD_SET(static_cast<int>(client.sckt), &setWrite);
			FD_SET(static_cast<int>(client.sckt), &setErrors);
			if (client.sckt > highestFd)
				highestFd = static_cast<int>(client.sckt);
		}
		selectResult = select(highestFd + 1, &setReads, &setWrite, &setErrors, &timeout);
		if (selectResult == -1)
		{
			std::cout << "Erreur select pour clients : " << std::endl;
			this->setRunningState(false);
		}
		else if (selectResult > 0)
		{
			this->handleCommands(setReads, setWrite, setErrors);
		}
	}
}

void launchGame(int port)
{
	Game startGame(port);
}

void Server::handleCommands(fd_set &setReads, fd_set &setWrite, fd_set &setErrors)
{
	Serialize serializer = {};
	auto itClient = clients.begin();
	while (itClient != clients.end())
	{
		bool hasError = false;
		const std::string clientAddress = this->m_serverSocket->getAddress(itClient->addr);
		const unsigned short clientPort = ntohs(itClient->addr.sin_port);
		socklen_t addrlen = sizeof(itClient->sckt);
		getsockname(this->m_serverSocket->getSocket(), (sockaddr *)&itClient->addr, &addrlen);

		if (FD_ISSET(itClient->sckt, &setErrors))
		{
			std::cerr << "Erreur" << std::endl;
			hasError = true;
		}
		else if (FD_ISSET(itClient->sckt, &setReads))
		{
			ClientTCPPacket_t clientPacket = {};
			char buffer[sizeof(clientPacket)] = {0};
			int ret = ::recv(itClient->sckt, &buffer, sizeof(clientPacket), 0);
			if (ret == 0)
			{
				std::cout << "Connexion terminee" << std::endl;
				hasError = true;
			}
			else if (ret == -1)
			{
				std::cerr << "Erreur reception : " << strerror(errno) << std::endl;
				hasError = true;
			}
			else
			{
				Serialize deserializer = {};
				deserializer.deserialize(buffer, &clientPacket, "TCP_CLIENT_PACKET_FC");

				if (clientPacket.type == PacketType::CREATE)
				{
					Server::Lobby lobby;
					std::stringstream tmp;
					std::string username = {0};
					tmp << clientPacket.username;
					tmp >> username;
					itClient->username = username;
					lobby.lobbyId = username;
					lobby.lobbyState = 0;
					lobby.createdBy = *itClient;
					(lobby.clientsLobby).push_back(*itClient); //.push_back(itClient);//
					this->lobbies.push_back(lobby);
					std::cout << "Lobby created by "<< itClient->username << " !\nNumber of curent lobby: " << (this->lobbies).size() << std::endl;
				}
				if (clientPacket.type == PacketType::JOIN)
				{
					std::stringstream fromClientRoomId;
					std::string roomId = {0};
					fromClientRoomId << clientPacket.roomId;
					fromClientRoomId >> roomId;
					for (auto &iterator : lobbies)
					{
						if (iterator.lobbyId == roomId)
						{
							std::stringstream tmp;
							std::string username = {0};
							tmp << clientPacket.username;
							tmp >> username;
							itClient->username = username;
							iterator.clientsLobby.push_back(*itClient);
							std::cout << username << " a rejoint le lobby " << roomId << "\n";
							std::string player_lobby = "";
							for (int i = 0; (int)iterator.clientsLobby.size() > i; i++) {
								player_lobby += iterator.clientsLobby[i].username + "|";
							}
							std::cout << player_lobby << std::endl;
							char n_buffer[sizeof(ServerTCPPacket_t)] = {0};
							serializer.serialize(n_buffer, "TCP_SERVER_PACKET", PacketType::LIST, player_lobby.c_str(), htons(0), sizeof(ServerTCPPacket_t));
							for (auto player_list : iterator.clientsLobby)
							{
								::send(player_list.sckt, n_buffer, sizeof(ServerTCPPacket_t), 0);
							}
							if (iterator.clientsLobby.size() == 4)
							{
								std::cout << "Game " << iterator.lobbyId << " can be launched" << std::endl;
								int range = 25000 - 3001 + 1;
								int port = rand() % range + 3001;
								std::cout << port << "\n";
								ths.push_back(std::thread(launchGame, port));
								char new_buffer[sizeof(ServerTCPPacket_t)] = {0};
								serializer.serialize(new_buffer, "TCP_SERVER_PACKET", PacketType::START, "", htons(port), sizeof(ServerTCPPacket_t));
								auto launchIt = iterator.clientsLobby.begin();
								while (launchIt != iterator.clientsLobby.end())
								{
									::send(launchIt->sckt, new_buffer, sizeof(ServerTCPPacket_t), 0);
									launchIt++;
								}
								break;
							}
						}
						else
						{
							std::cout << "Can't join this lobby -> Will display disconnect" << std::endl;
							hasError = true;
							break;
						}
					}
				}
				if (clientPacket.type == PacketType::LEAVE)
				{
					std::stringstream fromClientRoomId;
					std::string roomId = {0};
					fromClientRoomId << clientPacket.roomId;
					fromClientRoomId >> roomId;
					auto iterator = lobbies.begin();
					while (iterator != lobbies.end())
					{
						if (iterator->lobbyId == roomId) // lobbyName)
						{
							iterator->clientsLobby.erase(itClient);
							std::cout << "Lobby left!\n"
									  << iterator->lobbyId << std::endl;
							break;
						}
						else
						{
							hasError = true;
							break;
						}
					}
				}
				// SEND DATA HERE, WOULD USE IT TO SEND DATA TO ALL
				for (auto &cli : clients) {
					std::string lobbiesList = "";
					for (int i = 0; (int)this->lobbies.size() > i; i++) {
						lobbiesList += this->lobbies[i].lobbyId + ":" + std::to_string(this->lobbies[i].clientsLobby.size()) + "|";
					}
					char new_buffer[sizeof(ServerTCPPacket_t)] = {0};
					serializer.serialize(new_buffer, "TCP_SERVER_PACKET", PacketType::NONE, lobbiesList.c_str(), htons(0), sizeof(ServerTCPPacket_t));
					if (FD_ISSET(cli.sckt, &setWrite)) {
						ret = ::send(cli.sckt, new_buffer, sizeof(ServerTCPPacket_t), 0);
						if (ret == 0 || ret == -1) {
							std::cerr << "Erreur envoi" << std::endl;
							hasError = true;
						}
					}
				}
			}
		}
		if (hasError)
		{
			std::cout << "Deconnexion de [" << clientAddress << ":" << clientPort << "]" << std::endl;
			auto iterator = lobbies.begin();
			while (iterator != lobbies.end())
			{
				std::cout << "[" << itClient->username << "]" << std::endl;
				if (iterator->createdBy.username == itClient->username)
				{
					std::cout << "Lobby of " << iterator->createdBy.username << " deleted" << std::endl;
					iterator = lobbies.erase(iterator); //comprends pas
					break;
				}
				auto disconnectIt = iterator->clientsLobby.begin();
				while (disconnectIt != iterator->clientsLobby.end())
				{
					if (disconnectIt == itClient)
					{
						std::cout << "Ce client" << std::endl;
						break;
					}
					disconnectIt++;
				}
				iterator++;
			}
			itClient = clients.erase(itClient);
		}
		else
		{
			++itClient;
		}
	}
}

void Server::setRunningState(bool state)
{
	this->m_runningState = state;
}

void Server::stop()
{
	this->setRunningState(false);
}

Server::~Server()
{
	for (auto &th : ths)
	{
		if (th.joinable())
		{
			std::cout << "Joingnable" << std::endl;
			th.join();
		}
		else
		{
			std::cout << "Not joingnable" << std::endl;
		}
	}
	this->clients.clear();
}
