#ifndef MOVABLE_HPP
#define MOVABLE_HPP

#include "ecs/component/Component.hpp"
#include "util/Vec2.hpp"

class Movable : public Component {
public:
    Movable(const unsigned int speed);
    ~Movable();

    unsigned int getBaseSpeed() const;
    unsigned int getSpeed() const;
    void setSpeed(const unsigned int speed);
    Vec2i getDirection() const;
    void setDirection(const Vec2i &direction);
    Vec2i getComputedDirection(const float fElapsedTime) const;
    Vec2u getPosition() const;
    void setPosition(const Vec2u &position);
    bool isMoving() const;

private:
    unsigned int _baseSpeed;
    unsigned int _speed;
    Vec2i _direction;
    Vec2u _position;
};

#endif /* MOVABLE_HPP */
