#include "LobbyScene.hpp"
#include "util/Logger.hpp"
#include "util/Utils.hpp"
#include "Entity.hpp"
#include "Engine.hpp"
#include "Application.hpp"
#include "SceneManager.hpp"
#include "JoinScene.hpp"
#include "ConnectScene.hpp"
#include "ConnectScene_join.hpp"
#include <SFML/Audio.hpp>
#include <iostream>

LobbyScene::LobbyScene(const std::string &name) :
	Scene(name),
	background("background", -1, 3, sf::Vector2f(-1, 0), sf::Vector2f(0, 0), "assets/farback.gif", true),
	lobby("lobby", -1, 0, sf::Vector2f(-1, 0), sf::Vector2f(460, 200), "assets/lobby_display.png", true)
{
	font.loadFromFile("assets/Retro_Gaming.ttf");
	created = false;

	paralax_offset = 1;
}

void LobbyScene::onCreate()
{
}

void LobbyScene::update_user_list(std::string user_list_str) {
	JoinScene* join_scene = dynamic_cast<JoinScene*>(SceneManager::getInstance()->getScene(4));
	std::vector<std::string> user_vec = join_scene->split(user_list_str, '|');
	player_list.clear();
	sf::Vector2f position(525, 250);
	for (auto user : user_vec) {
		sf::Text *player = new sf::Text();
		player->setFont(font);
		player->setString(user);
		player->setCharacterSize(35);
		player->setPosition(position);
		player_list.push_back(*player);
		position.y += 60;
	}
	draw_user_list = true;
}

void LobbyScene::onDestroy()
{
}

bool LobbyScene::onEnable()
{
	if (created) {
		ConnectScene* connect_scene = dynamic_cast<ConnectScene*>(SceneManager::getInstance()->getScene(1));
		sf::Text *player = new sf::Text();
		player->setFont(font);
		player->setString(connect_scene->getPlayerName());
		player->setCharacterSize(35);
		sf::Vector2f position(525, 250);
		player->setPosition(position);
		player_list.push_back(*player);
	} else {
		draw_user_list = true;
	}

	return (true);
}

bool LobbyScene::onEvent(UNUSED const sf::Event &event, UNUSED sf::RenderWindow &window)
{
	return (true);
}

bool LobbyScene::onUpdate(UNUSED const float fElapsedTime)
{
	background.sprite.move(sf::Vector2f(-1 * background.speed, 0.f));
	if (background.sprite.getPosition().x < -1280.f)
		background.sprite.setPosition(sf::Vector2f(0, 0.f));
	return (true);
}

bool LobbyScene::onRender(UNUSED sf::RenderWindow &window)
{
	window.draw(background.sprite);
	window.draw(lobby.sprite);
	if (draw_user_list)
		for (auto &p: player_list)
			window.draw(p);
	return (true);
}

bool LobbyScene::onDisable()
{
	return (true);
}
