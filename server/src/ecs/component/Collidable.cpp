#include "ecs/component/Collidable.hpp"

Collidable::Collidable(const Vec2u size) :
    Component(ComponentType::COLLIDABLE_COMPONENT),
    _size(size)
{
}

Collidable::~Collidable()
{
}

Vec2u Collidable::getSize() const
{
    return (_size);
}

Vec2u Collidable::getOrigin() const
{
    return (_origin);
}

void Collidable::setOrigin(const Vec2u &origin)
{
    this->_origin = origin;
}

bool Collidable::isColliding(const Vec2u origin, const Vec2u size)
{
    if (_origin.x > origin.x + size.x || origin.x > _origin.x + _size.x)
        return (false);
    if (_origin.y < origin.y + size.y || origin.y < _origin.y + _size.y)
        return (false);
    return (true);
}
