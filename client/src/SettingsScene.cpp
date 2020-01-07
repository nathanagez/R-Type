

#include "SettingsScene.hpp"
#include "util/Logger.hpp"
#include "util/Utils.hpp"
#include "SceneManager.hpp"
#include <iostream>
#include "sockets.hpp"


SettingsScene::SettingsScene(const std::string &name) :
	Scene(name),
	background("background", -1, 3, sf::Vector2f(-1, 0), sf::Vector2f(0, 0), "assets/farback.gif", true),
	text_input("text_input", -1, 0, sf::Vector2f(-1, 0), sf::Vector2f(460, 250), "assets/text_input.png", true)
{
	font.loadFromFile("assets/Retro_Gaming.ttf");
	sf::Text address("", font);
	address.setCharacterSize(34);
	address.setFillColor(sf::Color::White);
	this->addr = address;
	this->addr.setPosition(520.f, 313.f);
}

void SettingsScene::onCreate()
{
	addr_prompt = Label::create("Enter server address", "assets/Retro_Gaming.ttf");
	addr_prompt->setPosition(sf::Vector2f(350, 150));
	addr_prompt->setCharacterSize(46);
	addr_prompt->setColor(sf::Color::White);
	addr_prompt->setHoverColor(sf::Color::Cyan);

	_back_to_menu = Button::create(
		"assets/button_back.png",
		"assets/button_back_pressed.png",
		sf::Vector2f(10.f, 10.f),
		[](UNUSED Button &button) {
			SceneManager::getInstance()->loadScene(0);
		}
	);
}

void SettingsScene::onDestroy()
{
}

bool SettingsScene::onEnable()
{
	return (true);
}

bool SettingsScene::onEvent(UNUSED const sf::Event &event, UNUSED sf::RenderWindow &window)
{
	_back_to_menu->handleEvent(window, event);
	addr_prompt->handleEvent(window, event);
	return (true);
}

bool SettingsScene::onUpdate(UNUSED const float fElapsedTime)
{
	return (true);
}

bool SettingsScene::onRender(UNUSED sf::RenderWindow &window)
{
	window.draw(background.sprite);
	_back_to_menu->draw(window);
	window.draw(text_input.sprite);
	addr_prompt->draw(window);
	return (true);
}

bool SettingsScene::onDisable()
{
	return (true);
}
