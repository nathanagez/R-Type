#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

class Scene {
	public:
		Scene(const std::string &name);
		virtual ~Scene();

		virtual void onCreate() = 0;
		virtual void onDestroy() = 0;

		virtual bool onEnable() = 0;
		virtual bool onEvent(const sf::Event &event, sf::RenderWindow &window) = 0;
		virtual bool onUpdate(const float fElapsedTime) = 0;
		virtual bool onRender(sf::RenderWindow &window) = 0;
		virtual bool onDisable() = 0;

		std::string getName() const;

	private:
		std::string _name;
};

#endif /* SCENE_HPP */
