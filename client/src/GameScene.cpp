
#include "GameScene.hpp"
#include "util/Logger.hpp"
#include "util/Utils.hpp"
#include "Entity.hpp"
#include "JoinScene.hpp"
#include <SFML/Audio.hpp>
#include <iostream>

Sockets *GameScene::client_udp;

GameScene::GameScene(const std::string &name) :
	Scene(name),
	background("background", -1, -2, sf::Vector2f(-1, 0), sf::Vector2f(0, 0), "assets/farback.gif", true),
	fg_stars("fg_stars", -1, -3, sf::Vector2f(-1, 0), sf::Vector2f(0, 0), "assets/fg_stars.png", true),
	game_over("game_over", 0, 0, sf::Vector2f(0, 0), sf::Vector2f(0, 0), "assets/game_over.png", true)
{
	font.loadFromFile("assets/Retro_Gaming.ttf");
	player_life = 100;
	score = 0;
	score_text.setFillColor(sf::Color::White);
	score_text.setCharacterSize(30);
	score_text.setPosition(sf::Vector2f(10, 10));
	score_text.setFont(font);
	boss_life = 200;
}

void GameScene::onCreate()
{
	buffer.loadFromFile("assets/pew.ogg");
	buffer_boom.loadFromFile("assets/boom.ogg");
	boom.setBuffer(buffer_boom);
	pew.setBuffer(buffer);
	direction = "";
	paralax_offset = 3;
}

void GameScene::onDestroy()
{
}

void GameScene::handleUDP_connection() {
	SceneManager::getInstance()->loadScene(3);
	char buffer_p_list[1024] = {0};
	int stop_list = 0;
	struct sockaddr_in cliaddr = {0};
	socklen_t addrlen = sizeof(cliaddr);
	stop_list = ::recvfrom(client_udp->getSocket(), &buffer_p_list, sizeof(buffer_p_list), 0, (struct sockaddr *)&cliaddr, &addrlen);
	buffer_p_list[stop_list] = '\0';

	std::vector<std::string> users = JoinScene::split(buffer_p_list, '|');
	GameScene* game_scene = dynamic_cast<GameScene*>(SceneManager::getInstance()->getScene(3));
	for (auto &u : users) {
		game_scene->user_list.push_back(u);
		std::cout << u << " has been added to userlist\n";
	}
	for (auto &user : game_scene->user_list) {
		bool found = false;
		for (auto &player : game_scene->player_list) {
			if (player->getName() == user) {
				found = true;
				break;
			}
		}
		if (!found) {
			std::vector<std::string>::iterator it = std::find(game_scene->user_list.begin(), game_scene->user_list.end(), user);
			int index = std::distance(game_scene->user_list.begin(), it);
			game_scene->player_list.push_back(new Entity(user, 100, 5, sf::Vector2f(0, 0), sf::Vector2f(120, 340), "assets/player"+std::to_string(index+1)+".png", true));
		}
	}
	char new_buffer[sizeof(EntityUDPPacket_t)] = {0};
	while (1) {
		memset(new_buffer, 0, sizeof(*new_buffer));
		struct sockaddr_in cliaddr = {0};
		socklen_t addrlen = sizeof(cliaddr);
		::recvfrom(client_udp->getSocket(), new_buffer, sizeof(new_buffer), 0, (struct sockaddr *)&cliaddr, &addrlen);
		EntityUDPPacket_t packet = {};
		Serialize deserializer = {};
		deserializer.deserialize(new_buffer, &packet, "UDP_CLIENT_PACKET");

		if (packet.type == GamePacketType::PLAYER_MOVE) {
			game_scene->players_structs.clear();
			game_scene->players_structs.push_back(packet.player1);
			game_scene->players_structs.push_back(packet.player2);
			game_scene->players_structs.push_back(packet.player3);
			game_scene->players_structs.push_back(packet.player4);
		}

		if (packet.type == GamePacketType::ENTITY_SPAWN) {
			int pos_x = ntohs(packet.entity.pos_x);
			int pos_y = ntohs(packet.entity.pos_y);
			int dir_x = ntohs(packet.entity.dir_x);
			int dir_y = ntohs(packet.entity.dir_y);
			std::stringstream stream;
			std::string texture_path = "";
			stream << packet.entity.texture;
			stream >> texture_path;
			std::cout << "ENTITY SPAWNED AT " << ntohs(packet.entity.pos_x) << " " << ntohs(packet.entity.pos_y) << " WITH VECTOR " << dir_x << " " << dir_y << "\n";
			std::string id = "";
			if (dir_x == 2) {
				if (texture_path == "assets/r-typesheet28.gif") {
					id = "boss";
				} else {
					id = "monster";
				}
			} else if (dir_x == 1) {
				if (game_scene->score >= 100) {
					id = "missile2";
					texture_path = "assets/missile_up.png";
				} else {
					id = "missile";
				}
			}
			game_scene->entity_list.push_back(new Entity(id, 0, ntohs(packet.entity.speed), sf::Vector2f(dir_x, dir_y), sf::Vector2f(pos_x, pos_y), texture_path, true));
		}
		if (packet.type == GamePacketType::ENTITY_DESTROY) {
			std::stringstream stream;
			std::string entity_id = {0};
			stream << packet.entity.texture;
			stream >> entity_id;
			for (auto &ent : game_scene->entity_list) {
				if (ent->debug_name == entity_id) {
					std::vector<Entity*>::iterator it = std::find(game_scene->entity_list.begin(), game_scene->entity_list.end(), ent);
					int index = std::distance(game_scene->entity_list.begin(), it);
					game_scene->entity_list.erase(it);
				}
			}
		}
	}
}

void GameScene::spawn_player_UDP() {
	ConnectScene* connect_scene = dynamic_cast<ConnectScene*>(SceneManager::getInstance()->getScene(1));
	char buffer[sizeof(EntityUDPPacket_t)] = {0};
	Serialize serializer = {};
	std::cout << connect_scene->getPlayerName().c_str() << " sent spawn\n";
	serializer.serialize(buffer, "UDP_CLIENT_PACKET", GamePacketType::SPAWN, 120, 340, 0, 0, connect_scene->getPlayerName().c_str(), sizeof(buffer));
	GameScene::client_udp->send(buffer, sizeof(buffer));
	GameScene::client_udp->send(buffer, sizeof(buffer));
}

void GameScene::move_UDP(UNUSED sf::Vector2f direction,UNUSED std::string username, sf::Vector2f position) {
	char buffer[sizeof(EntityUDPPacket_t)] = {0};
	Serialize serializer = {};
	serializer.serialize(buffer, "UDP_PLAYER_MOVE_PACKET", GamePacketType::PLAYER_MOVE, static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(direction.x), static_cast<int>(direction.y), username.c_str(), sizeof(EntityUDPPacket_t));
	GameScene::client_udp->send(buffer, sizeof(EntityUDPPacket_t));
}

void GameScene::fire_UDP(UNUSED std::string username) {
	char buffer[sizeof(EntityUDPPacket_t)] = {0};
	Serialize serializer = {};
	serializer.serialize(buffer, "UDP_PLAYER_FIRE_PACKET", GamePacketType::PLAYER_FIRE, username.c_str(), sizeof(buffer));
	GameScene::client_udp->send(buffer, sizeof(buffer));
}

bool GameScene::onEnable()
{
	ConnectScene* connect_scene = dynamic_cast<ConnectScene*>(SceneManager::getInstance()->getScene(1));
	my_username = connect_scene->getPlayerName();

	Engine::t1.join();
	std::cout << "starting T1" << "\n";
	Engine::t1 = std::thread(&GameScene::spawn_player_UDP);
	return (true);
}

bool GameScene::onEvent(UNUSED const sf::Event &event, UNUSED sf::RenderWindow &window)
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Left)
			direction += "LEFT ";
		else if (event.key.code == sf::Keyboard::Right)
			direction += "RIGHT ";
		else if (event.key.code == sf::Keyboard::Up)
			direction += "UP ";
		else if (event.key.code == sf::Keyboard::Down)
			direction += "DOWN ";
		else if (event.key.code == sf::Keyboard::Space) {
			pew.play();
			fire_UDP(my_username);
		}
		int dir_x = 0;
		int dir_y = 0;
		if (direction.find("LEFT") != std::string::npos)
			dir_x = 2;
		if (direction.find("RIGHT") != std::string::npos) {
			if (dir_x == 2)
				dir_x = 0;
			else
				dir_x = 1;
		}
		if (direction.find("UP") != std::string::npos)
			dir_y = 2;
		if (direction.find("DOWN") != std::string::npos) {
			if (dir_y == 2)
					dir_y = 0;
				else
					dir_y = 1;
		}
		for (auto &p : player_list) {
			if (p->debug_name == my_username) {
				move_UDP(sf::Vector2f(dir_x, dir_y), my_username, p->position);
			}
		}
	}
	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::Left)
			if (direction.find("LEFT") != std::string::npos)
				direction.erase(direction.find("LEFT "), 5);
		if (event.key.code == sf::Keyboard::Right)
			if (direction.find("RIGHT") != std::string::npos)
				direction.erase(direction.find("RIGHT "), 6);
		if (event.key.code == sf::Keyboard::Up)
			if (direction.find("UP") != std::string::npos)
				direction.erase(direction.find("UP "), 3);
		if (event.key.code == sf::Keyboard::Down)
			if (direction.find("DOWN") != std::string::npos)
				direction.erase(direction.find("DOWN "), 5);
		int dir_x = 0;
		int dir_y = 0;
		if (direction.find("LEFT") != std::string::npos)
			dir_x = 2;
		if (direction.find("RIGHT") != std::string::npos) {
			if (dir_x == 2)
				dir_x = 0;
			else
				dir_x = 1;
		}
		if (direction.find("UP") != std::string::npos)
			dir_y = 2;
		if (direction.find("DOWN") != std::string::npos) {
			if (dir_y == 2)
					dir_y = 0;
				else
					dir_y = 1;
		}
		for (auto &p : player_list) {
			if (p->debug_name == my_username) {
				move_UDP(sf::Vector2f(dir_x, dir_y), my_username, p->position);
			}
		}
	}
	return (true);
}

bool GameScene::onUpdate(UNUSED const float fElapsedTime)
{
	background.sprite.move(sf::Vector2f(1 * background.speed, 0.f));
	if (background.sprite.getPosition().x < -1280.f) {
		background.sprite.setPosition(sf::Vector2f(0, 0.f));
	}
	fg_stars.sprite.move(sf::Vector2f(1 * fg_stars.speed, 0.f));
	if (fg_stars.sprite.getPosition().x < -1280.f) {
		fg_stars.sprite.setPosition(sf::Vector2f(0, 0.f));
	}

	for (auto &entity : entity_list) {
		for (auto &player : player_list) {
			if (player->debug_name == my_username) {
				if ((entity->debug_name == "monster" || entity->debug_name == "boss") && entity->sprite.getGlobalBounds().intersects(player->sprite.getGlobalBounds())) {
					player_life -= 1;
				}
			}
		}
		if (entity->direction.x == 2)
			entity->direction.x = -1;
		if (entity->direction.y == 2)
			entity->direction.y = -1;
		entity->sprite.move(sf::Vector2f(entity->speed * entity->direction.x, entity->speed * entity->direction.y));
		for (auto &entity2 : entity_list) {
			if (((entity->debug_name == "missile" || entity->debug_name == "missile2") && entity2->debug_name == "monster") && entity->sprite.getGlobalBounds().intersects(entity2->sprite.getGlobalBounds())) {
				std::vector<Entity*>::iterator it = std::find(entity_list.begin(), entity_list.end(), entity);
				entity_list.erase(it);
				std::vector<Entity*>::iterator it2 = std::find(entity_list.begin(), entity_list.end(), entity2);
				entity_list.erase(it2);
				if (player_life > 0) {
					score += 10;
				}
				break;
			} else if ((entity->debug_name == "boss" && (entity2->debug_name == "missile" || entity2->debug_name == "missile2")) && entity->sprite.getGlobalBounds().intersects(entity2->sprite.getGlobalBounds())) {
				std::vector<Entity*>::iterator it = std::find(entity_list.begin(), entity_list.end(), entity2);
				entity_list.erase(it);
				if (boss_life < 0) {
					std::vector<Entity*>::iterator it = std::find(entity_list.begin(), entity_list.end(), entity);
					entity_list.erase(it);
					if (entity2->debug_name == "missile2") {
						boss_life -= 10;
					} else {
						boss_life -= 1;
					}
					break;
				} else {
					if (entity2->debug_name == "missile2") {
						boss_life -= 10;
					} else {
						boss_life -= 1;
					}
					break;
				}
			}
		}
	}

	for (auto &player : player_list) {
		for (auto &players_struct : players_structs) {
			std::stringstream stream;
			std::string name = {0};
			stream << players_struct.username;
			stream >> name;
			if (name == player->getName()) {
				if (players_struct.dir_x == 2)
					players_struct.dir_x = -1;
				if (players_struct.dir_y == 2)
					players_struct.dir_y = -1;
				player->sprite.move(sf::Vector2f(players_struct.dir_x * player->speed, players_struct.dir_y * player->speed));
				player->position = player->sprite.getPosition();
				break;
			}
		}
	}
	score_text.setString(std::to_string(score));
	return (true);
}

bool GameScene::onRender(UNUSED sf::RenderWindow &window)
{
	window.draw(background.sprite);
	window.draw(fg_stars.sprite);
	for (auto &entity : entity_list) {
		if (entity->debug_name != "boss") {
			window.draw(entity->sprite);
		} else {
			if (boss_life > 0) {
				window.draw(entity->sprite);
			}
		}
	}
	for (auto &player : player_list) {
		window.draw(player->sprite);
	}

	if (player_life < 0) {
		window.draw(game_over.sprite);
	}
	window.draw(score_text);
	return (true);
}

bool GameScene::onDisable()
{
	return (true);
}
