#include <iostream>

#include "Engine.hpp"
#include "EngineException.hpp"
#include "util/Logger.hpp"
#include "sockets.hpp"

std::atomic<bool> Engine::_isActive = ATOMIC_VAR_INIT(false);
std::thread Engine::t1;
std::thread Engine::t2;

Engine::Engine(const std::string &title, const sf::Vector2u &size, const bool debug) :
	sceneManager(SceneManager::getInstance()),
	_title(title),
	_size(size),
	_debug(debug)
{
	this->_fps = 0;
}

void Engine::start()
{
	if (_isActive) {
		LOG_WARNING("Engine", "The window couldn't be created because it is already active!");
		return;
	}

	if (!_debug)
		this->window = new sf::RenderWindow(
			sf::VideoMode(_size.x, _size.y, 32),
			_title,
			sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close
		);
	else
		this->window = new sf::RenderWindow(
				sf::VideoMode(_size.x, _size.y, 16),
				"[DEBUG] " + _title,
				sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close
		);

	if (!window)
		throw EngineException("The window couldn't be created!");
	else
		LOG_INFO("Engine", "The window has been successfully created.");

	this->_isActive = true;
	LOG_DEBUG("Engine", "The window has been activated.");

	startEngine();
}

void Engine::stop()
{
    if (!_isActive) {
		LOG_WARNING("Engine", "The window couldn't be closed because it isn't active!");
		return;
	}
	
	_isActive = false;
}

void Engine::startEngine()
{
	if (!onCreate()) {
		this->_isActive = false;
		LOG_DEBUG("Engine", "The engine hasn't been created due to \"onCreate()\" returning \"false\".");
	} else
		LOG_DEBUG("Engine", "The engine has been created.");

	if (!sceneManager->hasScenes())
		LOG_WARNING("SceneManager", "The scene manager doesn't have any scene!");

	auto elapsedTime1 = std::chrono::system_clock::now();
	auto elapsedTime2 = std::chrono::system_clock::now();
	float fElapsedTime = 0;
	float fFrameTimer = 1.0f;
	int nFrameCounter = 0;

	sf::Event event;

	sceneManager->loadScene(0);

	while (window->isOpen() && _isActive) {
		elapsedTime2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = elapsedTime2 - elapsedTime1;
		elapsedTime1 = elapsedTime2;
		fElapsedTime = elapsedTime.count();

		while (window->pollEvent(event)) {
			if (onEvent(event))
				sceneManager->getActiveScene()->onEvent(event, *window);
			if (!window->isOpen() || !_isActive)
				break;
		}

		if (!onUpdate(fElapsedTime) || !sceneManager->getActiveScene()->onUpdate(fElapsedTime)) {
			this->_isActive = false;
			LOG_DEBUG("Engine", "The engine has been deactivated due to \"onUpdate()\" returning \"false\".");
		}

		window->clear();
		sceneManager->getActiveScene()->onRender(*window);
		onRender();
		window->display();

		fFrameTimer += fElapsedTime;
		nFrameCounter += 1;
		if (fFrameTimer >= 1.0f) {
			fFrameTimer -= 1.0f;

			this->_fps = nFrameCounter;

			if (_debug) {
				window->setTitle("[DEBUG] " + _title + " [" + std::to_string(nFrameCounter) + " fps]");
				LOG_DEBUG(_title, "FPS " + std::to_string(nFrameCounter));
			}

			nFrameCounter = 0;
		}
	}

	if (t1.joinable()) {
		t1.join();
	}

	if (onDestroy()) {
		if (window->isOpen())
			window->close();

		this->_isActive = false;
		LOG_DEBUG("Engine", "The engine has been destroyed.");
	}
}
