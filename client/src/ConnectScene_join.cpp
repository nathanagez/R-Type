#include "ConnectScene_join.hpp"
#include "SceneManager.hpp"
#include "util/Logger.hpp"
#include "util/Utils.hpp"
#include "Entity.hpp"
#include "sockets.hpp"
#include "interfaces/IPackets.hpp"
#include "ConnectScene.hpp"
#include "serialize.hpp"
#include <SFML/Audio.hpp>
#include <iostream>

ConnectScene_join::ConnectScene_join(const std::string &name) :
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
}

std::string ConnectScene_join::getPlayerName() {
	return playerText.getString();
}

void ConnectScene_join::onCreate()
{
	_JoinLobbyList = Button::create(
		"assets/button_join.png",
		"assets/button_join_pressed.png",
		sf::Vector2f(601.f, 420.f),
		[](UNUSED Button &button) {
			ConnectScene* connect_scene = dynamic_cast<ConnectScene*>(SceneManager::getInstance()->getScene(1));
			connect_scene->command = 'l';
			Engine::t1 = std::thread(&ConnectScene::handleTCP_connection);
			SceneManager::getInstance()->loadScene(4);
		}
	);
	paralax_offset = 1;
}

void ConnectScene_join::onDestroy()
{
	// LOG_INFO(getName(), "onDestroy()");
}

bool ConnectScene_join::onEnable()
{
	background.sprite.setTexture(background.texture);
	text_input.sprite.setTexture(text_input.texture);
	text_input.sprite.setPosition(text_input.position);
	return (true);
}

bool ConnectScene_join::onEvent(UNUSED const sf::Event &event, UNUSED sf::RenderWindow &window)
{
	_JoinLobbyList->handleEvent(window, event);
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

bool ConnectScene_join::onUpdate(UNUSED const float fElapsedTime)
{
	background.sprite.move(sf::Vector2f(-1 * background.speed, 0.f));
	if (background.sprite.getPosition().x < -1280.f)
		background.sprite.setPosition(sf::Vector2f(0, 0.f));
	return (true);
}

bool ConnectScene_join::onRender(UNUSED sf::RenderWindow &window)
{
	window.draw(background.sprite);
	window.draw(text_input.sprite);
	window.draw(playerText);
	_JoinLobbyList->draw(window);
	return (true);
}

bool ConnectScene_join::onDisable()
{
	// LOG_INFO(getName(), "onDisable()");
	return (true);
}
