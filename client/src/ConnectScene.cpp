#include "ConnectScene.hpp"
#include "SceneManager.hpp"

#include "LobbyScene.hpp"
#include "JoinScene.hpp"
#include "GameScene.hpp"
#include "ConnectScene_join.hpp"
#include "util/Logger.hpp"
#include "util/Utils.hpp"
#include "Application.hpp"
#include "Engine.hpp"
#include "Entity.hpp"
#include "sockets.hpp"
#include "interfaces/IPackets.hpp"
#include <SFML/Audio.hpp>
#include <iostream>

ConnectScene::ConnectScene(const std::string &name) :
	Scene(name),
	background("background", -1, 3, sf::Vector2f(-1, 0), sf::Vector2f(0, 0), "assets/farback.gif", true),
	text_input("text_input", -1, 0, sf::Vector2f(-1, 0), sf::Vector2f(460, 250), "assets/text_input.png", true)
{
	font.loadFromFile("assets/Retro_Gaming.ttf");
	sf::Text playerText("", font);
	playerText.setCharacterSize(34);
	playerText.setFillColor(sf::Color::White);
	this->playerText = playerText;
	this->playerText.setPosition(520.f, 313.f);
	player1_name = "";
}

std::string ConnectScene::getPlayerName() {
	return playerText.getString();
}

void ConnectScene::setPlayerName(std::string username) {
	player1_name = username;
	playerText.setString(username);
}

void ConnectScene::handleTCP_connection() {
	ConnectScene* connect_scene = dynamic_cast<ConnectScene*>(SceneManager::getInstance()->getScene(1));
	if (connect_scene->command == 'c') {
		// SEND USERNAME TO CREATE LOBBY
		std::cout << connect_scene->getPlayerName().c_str() << "\n";
		char buffer[sizeof(ClientTCPPacket_t)] = {0};
		Serialize serializer = {};
		serializer.serialize(buffer, "TCP_CLIENT_PACKET_FC", PacketType::CREATE, connect_scene->getPlayerName().c_str(), sizeof(buffer));
		Application::client.send(buffer, sizeof(buffer));
		LobbyScene* lobby_scene = dynamic_cast<LobbyScene*>(SceneManager::getInstance()->getScene(2));
		lobby_scene->created = true;
		SceneManager::getInstance()->loadScene(2);
	}
	if (connect_scene->command == 'l') {
		// SEND USERNAME TO GET LOBBY
		char buffer[sizeof(ClientTCPPacket_t)] = {0};
		Serialize serializer = {};
		serializer.serialize(buffer, "TCP_CLIENT_PACKET_FC", PacketType::NONE, connect_scene->getPlayerName().c_str(), sizeof(buffer));
		Application::client.send(buffer, sizeof(buffer));
	}
	char new_buffer[sizeof(ServerTCPPacket_t)] = {0};
	while (1) {
		memset(new_buffer, 0, sizeof(new_buffer));
		::recv(Application::client.getSocket(), &new_buffer, sizeof(ServerTCPPacket_t), 0);
		ServerTCPPacket_t response = {};
		memcpy(&response, &new_buffer, sizeof(ServerTCPPacket_t));
		if (response.type == PacketType::START) {
			int port = ntohs(response.port);
			std::cout << port << "\n";
			GameScene* game_scene = dynamic_cast<GameScene*>(SceneManager::getInstance()->getScene(3));
			game_scene->client_udp = new Sockets("127.0.0.1", port, "UDP");
			Engine::t2 = std::thread(&GameScene::handleUDP_connection);
			break;
		}
		if (response.type == PacketType::LIST) {
			std::stringstream ss;
			std::string user_list_str = {0};
			ss << response.lobbies;
			ss >> user_list_str;
			std::cout << "RECEIVED USER LIST [" << user_list_str << "]\n";

			LobbyScene* lobby_scene = dynamic_cast<LobbyScene*>(SceneManager::getInstance()->getScene(2));
			lobby_scene->update_user_list(user_list_str);
		}
		if (response.type == PacketType::NONE) {
			LobbyScene* lobby_scene = dynamic_cast<LobbyScene*>(SceneManager::getInstance()->getScene(2));
			if (!lobby_scene->created) {
				std::cout << "RECEIVED LOBBY LIST\n";
				std::stringstream ss;
				std::string lobby_list_str = {0};
				ss << response.lobbies;
				ss >> lobby_list_str;
				std::cout << lobby_list_str << "\n";

				JoinScene* join_scene = dynamic_cast<JoinScene*>(SceneManager::getInstance()->getScene(4));
				join_scene->update_lobby_list(lobby_list_str);
			}
		}
	}
	std::cout << "T1 CLOSED" << "\n";
}

void ConnectScene::onCreate()
{
	_createRoom = Button::create(
		"assets/button_start.png",
		"assets/button_start_pressed.png",
		sf::Vector2f(601.f, 420.f),
		[](UNUSED Button &button) {
			ConnectScene* connect_scene = dynamic_cast<ConnectScene*>(SceneManager::getInstance()->getScene(1));
			connect_scene->command = 'c';
			Engine::t1 = std::thread(&ConnectScene::handleTCP_connection);
		}
	);
	paralax_offset = 1;
}

void ConnectScene::onDestroy()
{
	// LOG_INFO(getName(), "onDestroy()");
}

bool ConnectScene::onEnable()
{
	return (true);
}

bool ConnectScene::onEvent(UNUSED const sf::Event &event, UNUSED sf::RenderWindow &window)
{
	_createRoom->handleEvent(window, event);
	if (event.type == sf::Event::TextEntered) {
		if (event.key.code == 8) {
			if (player1_name.getSize() > 0)
				player1_name.erase(player1_name.getSize()-1, 1);
		} else if (player1_name.getSize() < 13)
			player1_name += event.text.unicode;
		playerText.setString(player1_name);
	}
	return (true);
}

bool ConnectScene::onUpdate(UNUSED const float fElapsedTime)
{
	background.sprite.move(sf::Vector2f(-1 * background.speed, 0.f));
	if (background.sprite.getPosition().x < -1280.f)
		background.sprite.setPosition(sf::Vector2f(0, 0.f));
	return (true);
}

bool ConnectScene::onRender(UNUSED sf::RenderWindow &window)
{
	window.draw(background.sprite);
	window.draw(text_input.sprite);
	window.draw(playerText);
	_createRoom->draw(window);
	return (true);
}

bool ConnectScene::onDisable()
{
	// LOG_INFO(getName(), "onDisable()");
	return (true);
}
