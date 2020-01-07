#include "util/Logger.hpp"
#include "Entity.hpp"
#include "util/Utils.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

Entity::Entity(const std::string &name, int life, int speed, sf::Vector2f direction, sf::Vector2f position, std::string texture_path, bool is_displayed)
{
	this->debug_name = name;
		// std::string id;
	this->life = life;
	this->speed = speed;
	this->position = position;
	this->direction = direction;
	while (!texture.loadFromFile(texture_path)) {
	}
	sprite.setTexture(texture);
	sprite.setPosition(position);

	this->is_displayed = is_displayed;
	// LOG_DEBUG("EntityManager", "Entity \"" + debug_name + "\" has been created.");
}

Entity::~Entity()
{
	LOG_DEBUG("EntityManager", "Entity \"" + debug_name + "\" has been destroyed.");
}

std::string Entity::getName() const
{
	return (debug_name);
}
