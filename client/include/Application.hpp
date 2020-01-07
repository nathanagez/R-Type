#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Engine.hpp"
#include "sockets.hpp"

class Application : public Engine {
	public:
		Application(const std::string &title, const sf::Vector2u &size, const bool debug = false);

		bool onCreate();
		bool onDestroy();

		bool onEvent(const sf::Event &event);
		bool onUpdate(const float fElapsedTime);
		bool onRender();
		static Sockets client;
};

#endif /* APPLICATION_HPP */
