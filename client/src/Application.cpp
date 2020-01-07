#include "Application.hpp"
#include "MenuScene.hpp"
#include "GameScene.hpp"
#include "LobbyScene.hpp"
#include "JoinScene.hpp"
#include "ConnectScene.hpp"
#include "SettingsScene.hpp"
#include "ConnectScene_join.hpp"
#include "util/Utils.hpp"
#include <iostream>

Sockets Application::client("127.0.0.1", 3000, "TCP");


Application::Application(const std::string &title, const sf::Vector2u &size, const bool debug) :
	Engine(title, size, debug)
{
}

bool Application::onCreate()
{
	window->setFramerateLimit(60);
	window->setKeyRepeatEnabled(false);

	sceneManager->registerScene(new MenuScene("MenuScene"), true);
	sceneManager->registerScene(new ConnectScene("ConnectScene"));
	sceneManager->registerScene(new LobbyScene("LobbyScene"));
	sceneManager->registerScene(new GameScene("GameScene"));
	sceneManager->registerScene(new JoinScene("JoinScene"));
	sceneManager->registerScene(new ConnectScene_join("ConnectScene_join"));
	sceneManager->registerScene(new SettingsScene("SettingsScene"));

	return (true);
}

bool Application::onDestroy()
{
	return (true);
}

bool Application::onEvent(UNUSED const sf::Event &event)
{
	if (event.type == sf::Event::Closed) {
		if (Engine::t1.joinable()) {
			std::cout << "Detach t1\n";
			Engine::t1.detach();
		}
		if (Engine::t2.joinable()) {
			std::cout << "Detach t2\n";
			Engine::t2.detach();
		}
		window->close();
	}
	return (true);
}

bool Application::onUpdate(UNUSED const float fElapsedTime)
{
	return (true);
}

bool Application::onRender()
{
	return (true);
}
