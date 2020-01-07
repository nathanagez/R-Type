#include <vector>
#include <algorithm>
#include "game.hpp"
#include "sockets.hpp"
#include "serialize.hpp"
#include <chrono>

std::thread Game::game_thread;

void Game::game_udp_handler(std::vector<EntityUDPPacket_t> *players, int m_socket) {
	Serialize serializer = {};
	tmpPlayer_t p = {};
	//char buffer[sizeof(EntityUDPPacket_t)] = {0};
	char new_buffer[sizeof(EntityUDPPacket_t)] = {0};

	while (1)
	{
		std::cout << "segf10" << std::endl;
		char buffer[sizeof(EntityUDPPacket_t)] = {0};
		EntityUDPPacket_t Entity = {};
		std::cout << "segf11" << std::endl;

		struct sockaddr_in cliaddr = {};
		std::cout << "segf12" << std::endl;
		socklen_t addrlen = sizeof(cliaddr);
		int received = ::recvfrom(m_socket, &buffer, sizeof(EntityUDPPacket_t), 0, (struct sockaddr *)&cliaddr, &addrlen);
		std::cout << "segf13" << std::endl;
		std::cout << "Received  bytes : " << received << "\n";
		serializer.deserialize(buffer, &Entity, "UDP_CLIENT_PACKET");
		std::cout << "segf14" << std::endl;
		if (Entity.type == GamePacketType::SPAWN)
		{
			//UDPClient new_client;
			EntityUDPPacket_t new_client = {};
			std::cout << "segf1" << std::endl;
			memcpy(&new_client.player, &Entity.player, sizeof(Entity.player));
			std::cout << "segf1 inter memcpy" << std::endl;
			memcpy(&new_client.player.cliaddr, &cliaddr, addrlen);
			std::cout << "segf2" << std::endl;
			bool found = false;
			for (auto nclient : *players) {
				std::stringstream stream1n;
				std::string str1 = {0};
				stream1n << nclient.player.username;
				stream1n >> str1;
				std::stringstream stream2n;
				std::string str2 = {0};
				stream2n << new_client.player.username;
				stream2n >> str2;
				std::cout << "segf1.1" << std::endl;
				std::cout << "comparing : " << str1 << " with : " << str2 << std::endl;
				if (str1 == str2) {
					std::cout << "found" << std::endl;
					found = true;
					break;
				}
				std::cout << "segf1.2" << std::endl;
			}
			if (!found) {
				std::cout << new_client.player.username << " added" << std::endl;
				std::cout << "segf3" << std::endl;
				players->push_back(new_client);
				std::cout << "segf4" << std::endl;
				EntityManager::Ptr manager = EntityManager::getInstance();
				std::stringstream stream;
				std::string str = {0};
				stream << new_client.player.username;
				stream >> str;
				std::cout << "segf5" << std::endl;
				manager->createPlayer(str);
				std::cout << "segf6" << std::endl;
			}
			if (players->size() == 4) {
				std::string playerList = "";
				for (auto &player : *players)
				{
					std::stringstream stream;
					std::string str = {0};
					stream << player.player.username;
					stream >> str;
					playerList += str + "|";
				}
				for (auto &player : *players)
				{
					std::cout << "SENT PLAYERLIST : [" << playerList.c_str() << "]\n";
					int sent = ::sendto(m_socket, playerList.c_str(), playerList.size(),
					0, (const struct sockaddr *)&player.player.cliaddr, sizeof(player.player.cliaddr));
					std::cout << player.player.username << " " << sent << std::endl;
				}
			}
		}
		else if (Entity.type == GamePacketType::PLAYER_MOVE)
		{
			std::stringstream stream;
			std::string username = {0};
			stream << Entity.player1.username;
			stream >> username;
			int index = 1;
			for (auto &finder: *players) {
				std::stringstream stream1;
				std::string cmp1 = {0};
				struct sockaddr_in socktmp;
				stream1 << finder.player.username;
				stream1 >> cmp1;
				memcpy(&socktmp, &finder.player.cliaddr, sizeof(socktmp));
				if (cmp1 == username) {
					switch (index) {
						case 1:
							memcpy(&p.player1, &Entity.player1, sizeof(p.player1));
							memcpy(&finder.player, &Entity.player1, sizeof(finder.player));
							memcpy(&finder.player.cliaddr, &socktmp, sizeof(socktmp));
							break;
						case 2:
							memcpy(&p.player2, &Entity.player1, sizeof(p.player2));
							memcpy(&finder.player, &Entity.player1, sizeof(finder.player));
							memcpy(&finder.player.cliaddr, &socktmp, sizeof(socktmp));
							break;
						case 3:
							memcpy(&p.player3, &Entity.player1, sizeof(p.player3));
							memcpy(&finder.player, &Entity.player1, sizeof(finder.player));
							memcpy(&finder.player.cliaddr, &socktmp, sizeof(socktmp));
							break;
						case 4:
							memcpy(&p.player4, &Entity.player1, sizeof(p.player4));
							memcpy(&finder.player, &Entity.player1, sizeof(finder.player));
							memcpy(&finder.player.cliaddr, &socktmp, sizeof(socktmp));
							break;
					}
					break;
				}
				index++;
			}
			memset(new_buffer, 0, sizeof(*new_buffer));

			serializer.serialize(new_buffer, "UDP_PLAYER_MOVE_PACKET_SERVER", GamePacketType::PLAYER_MOVE,
			p.player1.pos_x, p.player1.pos_y, p.player1.dir_x, p.player1.dir_y, p.player1.username,
			p.player2.pos_x, p.player2.pos_y, p.player2.dir_x, p.player2.dir_y, p.player2.username,
			p.player3.pos_x, p.player3.pos_y, p.player3.dir_x, p.player3.dir_y, p.player3.username,
			p.player4.pos_x, p.player4.pos_y, p.player4.dir_x, p.player4.dir_y, p.player4.username,
			sizeof(EntityUDPPacket_t));
			std::cout << "Playername 1 [username: " << p.player1.username << " x: " << ntohs(p.player1.dir_x) << " y: " << ntohs(p.player1.dir_y) << " POS_X " << ntohs(p.player1.pos_x) << " Y: " << ntohs(p.player1.pos_y) << " ]" << std::endl;
			std::cout << "Playername 2 [username: " << p.player2.username << " x: " << ntohs(p.player2.dir_x) << " y: " << ntohs(p.player2.dir_y) << " POS_X " << ntohs(p.player2.pos_x) << " Y: " << ntohs(p.player2.pos_y) << " ]" << std::endl;
			std::cout << "Playername 3 [username: " << p.player3.username << " x: " << ntohs(p.player3.dir_x) << " y: " << ntohs(p.player3.dir_y) << " POS_X " << ntohs(p.player3.pos_x) << " Y: " << ntohs(p.player3.pos_y) << " ]" << std::endl;
			std::cout << "Playername 4 [username: " << p.player4.username << " x: " << ntohs(p.player4.dir_x) << " y: " << ntohs(p.player4.dir_y) << " POS_X " << ntohs(p.player4.pos_x) << " Y: " << ntohs(p.player4.pos_y) << " ]" << std::endl;
			for (auto &player : *players)
			{
				::sendto(m_socket, new_buffer, sizeof(EntityUDPPacket_t),
				0, (const struct sockaddr *)&player.player.cliaddr, sizeof(player.player.cliaddr));
			}
		} else if (Entity.type == GamePacketType::PLAYER_FIRE) {
			// FIRED
			std::cout << "FIRED" << std::endl;
			std::stringstream stream;
			std::string username = {0};
			stream << Entity.username;
			stream >> username;
			int index = 1;
			char bullet_buffer[sizeof(EntityUDPPacket_t)] = {0};
			IEntity *missile = EntityManager::getInstance()->createEntity("Missile.so");
			auto movable = dynamic_cast<Movable*>(missile->getComponent(ComponentType::MOVABLE_COMPONENT));
			for (auto &finder: *players) {
				memset(bullet_buffer, 0, sizeof(*bullet_buffer));

				std::stringstream stream1;
				std::string cmp1 = {0};
				struct sockaddr_in socktmp = {};
				stream1 << finder.player.username;
				stream1 >> cmp1;
				int ret = 0;
				if (cmp1 == username) {
					switch (index) {
						case 1:
							std::cout << "[1] POS_X: " << ntohs(p.player1.pos_x) << " POS_Y: " << ntohs(p.player1.pos_y) << " \n";
							movable->setPosition(Vec2u(
								ntohs(p.player1.pos_x),
								ntohs(p.player1.pos_y)
							));
							std::cout << "2" << "\n";
							movable->setDirection(Vec2i(1, 0));
							std::cout << "3" << "\n";
							missile->serialize(bullet_buffer, "SPAWN");
							std::cout << "4" << "\n";
							for (auto &bullet : *players) {
								ret = ::sendto(m_socket, bullet_buffer, sizeof(EntityUDPPacket_t),
								0, (const struct sockaddr *)&bullet.player.cliaddr, sizeof(bullet.player.cliaddr));
								std::cout << "Sent missile [ x:" << ntohs(p.player1.pos_x) << " y:" << ntohs(p.player1.pos_y) << "] to " << bullet.player.username << std::endl;
							}
							break;
						case 2:
							std::cout << "[2] POS_X: " << ntohs(p.player2.pos_x) << " POS_Y: " << ntohs(p.player2.pos_y) << " \n";
							movable->setPosition(Vec2u(
								ntohs(p.player2.pos_x),
								ntohs(p.player2.pos_y)
							));
							std::cout << "2" << "\n";
							movable->setDirection(Vec2i(1, 0));
							std::cout << "3" << "\n";
							missile->serialize(bullet_buffer, "SPAWN");
							std::cout << "4" << "\n";
							for (auto &bullet : *players) {
								ret = ::sendto(m_socket, bullet_buffer, sizeof(EntityUDPPacket_t),
								0, (const struct sockaddr *)&bullet.player.cliaddr, sizeof(bullet.player.cliaddr));
								std::cout << "Sent missile [ x:" << ntohs(p.player2.pos_x) << " y:" << ntohs(p.player2.pos_y) << "] to " << bullet.player.username << std::endl;
							}
							break;
						case 3:
							std::cout << "[3] POS_X: " << p.player3.pos_x << "POS_Y: " << p.player3.pos_y << " \n";
							movable->setPosition(Vec2u(
								ntohs(p.player3.pos_x),
								ntohs(p.player3.pos_y)
							));
							std::cout << "2" << "\n";
							movable->setDirection(Vec2i(1, 0));
							std::cout << "3" << "\n";
							missile->serialize(bullet_buffer, "SPAWN");
							std::cout << "4" << "\n";
							for (auto &bullet : *players)
							{
							ret = ::sendto(m_socket, bullet_buffer, sizeof(EntityUDPPacket_t),
							0, (const struct sockaddr *)&bullet.player.cliaddr, sizeof(bullet.player.cliaddr));
							std::cout << "Send missile [ x:" << p.player3.pos_x << " y:" << p.player3.pos_y << "]" << std::endl;
							}
							break;
						case 4:
							std::cout << "[4] POS_X: " << p.player4.pos_x << "POS_Y: " << p.player4.pos_y << " \n";
							movable->setPosition(Vec2u(
								ntohs(p.player4.pos_x),
								ntohs(p.player4.pos_y)
							));
							std::cout << "2" << "\n";
							movable->setDirection(Vec2i(1, 0));
							std::cout << "3" << "\n";
							missile->serialize(bullet_buffer, "SPAWN");
							std::cout << "4" << "\n";
							for (auto &bullet : *players)
							{
							ret = ::sendto(m_socket, bullet_buffer, sizeof(EntityUDPPacket_t),
							0, (const struct sockaddr *)&bullet.player.cliaddr, sizeof(bullet.player.cliaddr));
							std::cout << "Send missile [ x:" << p.player4.pos_x << " y:" << p.player4.pos_y << "]" << std::endl;
							}
							break;
					}
					break;
				}
				index++;
			}
		}
	}
}


Game::Game(int port) : m_port(port)
{
	Sockets UDPGameSocket(m_port, 0, "UDP");
	this->m_socket = UDPGameSocket.getSocket();
	std::cout << "Socket in" << std::endl;

	game_thread = std::thread(game_udp_handler, &players, m_socket);

	EntityManager::Ptr manager = EntityManager::getInstance();

	auto elapsedTime1 = std::chrono::system_clock::now();
	auto elapsedTime2 = std::chrono::system_clock::now();
	float fElapsedTime = 0.f;

	unsigned int wave = 0;
	unsigned int score = 0;
	float spawnCooldown = 3.f;
	float cooldown = spawnCooldown;

	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	while (1) {

		elapsedTime2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = elapsedTime2 - elapsedTime1;
		elapsedTime1 = elapsedTime2;
		fElapsedTime = elapsedTime.count();

		if (cooldown <= 0) {
			cooldown = spawnCooldown;
			wave += 1;
			std::cout << "SPAWNED MOB" << std::endl;
			if (wave != 5) {
				for (unsigned int i = 0; i != 5; i += 1)
					sendTo(manager->createEntity("Mob.so"), "SPAWN");
			} else {
				sendTo(manager->createEntity("Boss.so"), "SPAWN");
			}
		} else {
			cooldown -= fElapsedTime;
		}
		for (auto *entite : manager->getAllEntities()) {
			std::cout << entite->getName() << "\n";
			/* 			auto *movable = dynamic_cast<Movable*>(entite->getComponent(ComponentType::MOVABLE_COMPONENT));
			if (movable->getPosition().x < 0) {
				std::cout << "DESTROYED" << "\n";
				manager->destroyEntity(entite->getId());
			} */
		}

		for (ISystem *system : SystemManager::getInstance()->getAllSystems())
			for (IEntity *entity : manager->getAllEntities())
				system->update(entity, fElapsedTime);


	}

}

void Game::sendTo(IEntity *entity, const std::string &packet)
{
	char buffer[sizeof(EntityUDPPacket_t)] = {0};
	entity->serialize(buffer, packet);
	int ret = 0;
	for (auto player : players)
	{
		ret = ::sendto(m_socket, buffer, sizeof(EntityUDPPacket_t),
		0, (const struct sockaddr *)&player.player.cliaddr, sizeof(player.player.cliaddr));
		std::cout << "Send value [" << ret << "]" << std::endl;
	}
}