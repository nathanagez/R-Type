#include "JoinScene.hpp"
#include "util/Logger.hpp"
#include "util/Utils.hpp"
#include "Entity.hpp"
#include "SceneManager.hpp"
#include "ConnectScene.hpp"
#include "Application.hpp"
#include "ConnectScene_join.hpp"
#include <SFML/Audio.hpp>
#include <iostream>

/*
 * TODO: add lobby LIST::WIDGET
 */

JoinScene::JoinScene(const std::string &name) :
	Scene(name),
	background("background", -1, 3, sf::Vector2f(-1, 0), sf::Vector2f(0, 0), "assets/farback.gif", true),
	Join("Join", -1, 0, sf::Vector2f(-1, 0), sf::Vector2f(350, 90), "assets/lobby_display.png", true)
{
	draw_lobby_list = false;
	// name
}

void JoinScene::onCreate()
{
}

std::vector<std::string> JoinScene::split(const std::string &s, char delim) {
	std::vector<std::string> result;
	std::stringstream ss(s);
	std::string item = {0};

	while (getline(ss, item, delim)) {
		result.push_back(item);
	}

	return result;
}

void JoinScene::onDestroy()
{
	// LOG_INFO(getName(), "onDestroy()");
}

bool JoinScene::onEnable()
{
	_back_to_menu = Button::create(
		"assets/button_back.png",
		"assets/button_back_pressed.png",
		sf::Vector2f(10.f, 10.f),
		[](UNUSED Button &button) {
			SceneManager::getInstance()->loadScene(0);
		}
	);
	Join.sprite.setTexture(Join.texture);
	Join.sprite.setPosition(Join.position);
	Join.sprite.setScale(1.5, 1.5);
	paralax_offset = 1;

	return (true);
}

void JoinScene::update_lobby_list(std::string lobby_list_str) {
	JoinScene* join_scene = dynamic_cast<JoinScene*>(SceneManager::getInstance()->getScene(4));
	join_scene->lobby_list = List::create();
	join_scene->lobby_list->setPosition(sf::Vector2f(420, 160));
	join_scene->lobby_list->setSize(sf::Vector2f(490.f, 400.f));
	std::vector<std::string> lobby_vec = join_scene->split(lobby_list_str, '|');
	for (auto &lobby_elem : lobby_vec) {
		std::vector<std::string> lobby_elem_split = join_scene->split(lobby_elem, ':');
		Label::Ptr lobby = Label::create(lobby_elem_split[0] + "\t\t" + lobby_elem_split[1] + "/4", "assets/Retro_Gaming.ttf");
		lobby->setPadding(sf::Vector2f(0, 15));
		lobby->setCharacterSize(46);
		lobby->setHoverColor(sf::Color::White);
		lobby->onClick([](UNUSED Label &lob) {
			std::string str = lob.getText();
			std::size_t found = str.find("\t");
			if (found != std::string::npos) {
				std::string lobby_name = str.substr(0, found);
				ConnectScene_join* connect_scene_join = dynamic_cast<ConnectScene_join*>(SceneManager::getInstance()->getScene(5));
				connect_scene_join->lobby_name = lobby_name;
				char buffer[sizeof(ClientTCPPacket_t)] = {0};
				Serialize serializer = {};
				serializer.serialize(buffer, "TCP_CLIENT_PACKET", PacketType::JOIN, connect_scene_join->getPlayerName().c_str(), lobby_name.c_str(), sizeof(ClientTCPPacket_t));
				Application::client.send(buffer, sizeof(buffer));
				ConnectScene* connect_scene = dynamic_cast<ConnectScene*>(SceneManager::getInstance()->getScene(1));
				connect_scene->setPlayerName(connect_scene_join->getPlayerName());
				SceneManager::getInstance()->loadScene(2);
			}
		});
		join_scene->lobby_list->addItem(lobby);
	}
	join_scene->lobby_list->setBackgroundColor(sf::Color::Transparent);
	join_scene->draw_lobby_list = true;
}


bool JoinScene::onEvent(UNUSED const sf::Event &event, UNUSED sf::RenderWindow &window)
{
	_back_to_menu->handleEvent(window, event);
	if (draw_lobby_list)
		lobby_list->handleEvent(window, event);
	return (true);
}

bool JoinScene::onUpdate(UNUSED const float fElapsedTime)
{
	background.sprite.move(sf::Vector2f(-1 * background.speed, 0.f));
	if (background.sprite.getPosition().x < -1280.f)
		background.sprite.setPosition(sf::Vector2f(0, 0.f));
	return (true);
}

bool JoinScene::onRender(UNUSED sf::RenderWindow &window)
{
	window.draw(background.sprite);
	_back_to_menu->draw(window);
	window.draw(Join.sprite);
	if (draw_lobby_list)
		lobby_list->draw(window);
	return (true);
}

bool JoinScene::onDisable()
{
	LOG_INFO(getName(), "onDisable()");
	return (true);
}
