#include "ecs/entity/Player.hpp"

Player::Player(const std::string &name) :
    Entity(EntityType::PLAYER_ENTITY, name, "")
{
}

Player::~Player()
{
}

void Player::init()
{
}

void Player::update()
{
}

void Player::serialize(char *buff, const std::string &packet)
{
}
