#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

class Entity {
	public:
		Entity(const std::string &name, int life, int speed, sf::Vector2f direction, sf::Vector2f position, std::string texture_path, bool is_displayed);
		virtual ~Entity();

		// virtual void onCreate() = 0;
		// virtual void onDestroy() = 0;

		std::string getName() const;

		sf::Texture texture;
		sf::Sprite sprite;
		int speed;
		sf::Vector2f position;
		bool is_displayed;
		sf::Vector2f direction;
		std::string debug_name;
	private:
		std::string id;
		int life;
};

#endif /* ENTITY_HPP */
