

#include "Application.hpp"
#include "MenuScene.hpp"
#include "util/Logger.hpp"
#include "util/Utils.hpp"
#include "SceneManager.hpp"
#include <iostream>
#include "sockets.hpp"

/*
 * TODO: change background + fg to entity
 */

MenuScene::MenuScene(const std::string &name) :
	Scene(name)
{
	alien_offset = 0;
	alien_anim = 0.1;
}

void MenuScene::onCreate()
{
	music.openFromFile("assets/soundtrack.ogg");
	music.setVolume(20);
	music.play();
	background_texture.loadFromFile("assets/background.png");
	alien_texture.loadFromFile("assets/alien.png");

	fg_texture.loadFromFile("assets/fg_stars.png");

	_startButton = Button::create(
		"assets/boilerplate_side_btn_new_game.png",
		"assets/boilerplate_side_btn_pressed_new_game.png",
		sf::Vector2f(991.f, 120.f),
		[](UNUSED Button &button) {
			SceneManager::getInstance()->loadScene(1);
		}
	);
	_joinButton = Button::create(
		"assets/boilerplate_side_btn_join_game.png",
		"assets/boilerplate_side_btn_pressed_join_game.png",
		sf::Vector2f(991.f, 240.f),
		[](UNUSED Button &button) {
			SceneManager::getInstance()->loadScene(5);
		}
	);
	_settingsButton = Button::create(
		"assets/boilerplate_side_btn_settings.png",
		"assets/boilerplate_side_btn_pressed_settings.png",
		sf::Vector2f(991.f, 360.f),
		[](UNUSED Button &button) {
			SceneManager::getInstance()->loadScene(6);
		}
	);
	_quitButton = Button::create(
		"assets/boilerplate_side_btn_quit.png",
		"assets/boilerplate_side_btn_pressed_quit.png",
		sf::Vector2f(991.f, 480.f),
		[](UNUSED Button &button) {
			// CLOSE THE WINDOW
			Application::stop();
		}
	);
}

void MenuScene::onDestroy()
{
}

bool MenuScene::onEnable()
{
	background_sprite.setTexture(background_texture);
	fg_sprite.setTexture(fg_texture);
	alien_sprite.setTexture(alien_texture);
	alien_sprite.setTextureRect(sf::IntRect(alien_offset, 0, 400, 400));
	alien_sprite.setPosition(sf::Vector2f(180, 200));
	alien_sprite.setScale(1.5, 1.5);
	return (true);
}

bool MenuScene::onEvent(UNUSED const sf::Event &event, UNUSED sf::RenderWindow &window)
{
	_startButton->handleEvent(window, event);
	_joinButton->handleEvent(window, event);
	_settingsButton->handleEvent(window, event);
	_quitButton->handleEvent(window, event);
	return (true);
}

bool MenuScene::onUpdate(UNUSED const float fElapsedTime)
{
	if (alien_anim < 0) {
		if (alien_offset < 11600) {
			alien_sprite.setTextureRect(sf::IntRect(alien_offset, 0, 400, 400));
			alien_offset += 400;
		} else {
			alien_offset = 0;
		}
		alien_anim = 0.1;
	}
	alien_anim -= fElapsedTime;
	return (true);
}

bool MenuScene::onRender(UNUSED sf::RenderWindow &window)
{
	window.draw(background_sprite);
	window.draw(fg_sprite);
	window.draw(background_sprite);
	_startButton->draw(window);
	_joinButton->draw(window);
	_settingsButton->draw(window);
	_quitButton->draw(window);
	window.draw(alien_sprite);
	return (true);
}

bool MenuScene::onDisable()
{
	return (true);
}
