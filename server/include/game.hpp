#ifndef _GAME_H
#define _GAME_H

#include "interfaces/IGame.hpp"
#include "interfaces/IPackets.hpp"
#include <thread>
#include "ecs/EntityManager.hpp"
#include "ecs/SystemManager.hpp"
#include "ecs/component/Component.hpp"
#include "ecs/component/Damageable.hpp"
#include <chrono>
#include "ecs/component/Movable.hpp"

#include <future>
#include <iostream>
#include <thread>
#include <utility>

class Game : public IGame
{
	public:
		Game(int port);
	private:
		typedef struct Player {
			struct sockaddr_in cliaddr;
			std::string username;
		} Player_t;
		int m_port;
		int m_socket;
		void sendTo(IEntity *entity, const std::string &packet);
		std::vector<EntityUDPPacket_t> players;
		static std::thread game_thread;
		static void game_udp_handler(std::vector<EntityUDPPacket_t> *players, int m_socket);

};

#endif
