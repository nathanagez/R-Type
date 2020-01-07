#include "ecs/component/Movable.hpp"

Movable::Movable(const unsigned int speed) :
    Component(ComponentType::MOVABLE_COMPONENT),
    _baseSpeed(speed),
    _speed(speed)
{
}

Movable::~Movable()
{
}

unsigned int Movable::getBaseSpeed() const
{
    return (_baseSpeed);
}

unsigned int Movable::getSpeed() const
{
    return (_speed);
}

void Movable::setSpeed(const unsigned int speed)
{
    this->_speed = speed;
}

Vec2i Movable::getDirection() const
{
    return (_direction);
}

void Movable::setDirection(const Vec2i &direction)
{
    this->_direction = direction;
}

Vec2i Movable::getComputedDirection(const float fElapsedTime) const
{
    return ((_direction - 1) * (_speed * fElapsedTime));
}

Vec2u Movable::getPosition() const
{
    return (_position);
}

void Movable::setPosition(const Vec2u &position)
{
    this->_position = position;
}

bool Movable::isMoving() const
{
    return (_direction.x != 0 || _direction.y != 0);
}
