#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <atomic>
#include <chrono>
#include <string>

#include <SFML/Graphics.hpp>
#include <thread>

#include "EngineException.hpp"
#include "SceneManager.hpp"
#include "sockets.hpp"

class Engine {
	public:
		Engine(const std::string &title, const sf::Vector2u &size, const bool debug = false);

        void start();
        static void stop();

		virtual bool onCreate() = 0;
		virtual bool onDestroy() = 0;

		virtual bool onEvent(const sf::Event &event) = 0;
		virtual bool onUpdate(const float fElapsedTime) = 0;
		virtual bool onRender() = 0;

		static std::thread t1;
		static std::thread t2;

	protected:
		sf::RenderWindow *window;
		SceneManager::Ptr sceneManager;

	private:
		void startEngine();

		static std::atomic<bool> _isActive;

		std::string _title;
		sf::Vector2u _size;
		bool _debug;

		int _fps;
};

#endif /* ENGINE_HPP */
