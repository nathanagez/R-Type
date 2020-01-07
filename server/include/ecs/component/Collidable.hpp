#ifndef Collidable_HPP
#define Collidable_HPP

#include "ecs/component/Component.hpp"
#include "util/Vec2.hpp"

class Collidable : public Component {
public:
    Collidable(const Vec2u size);
    ~Collidable();

    Vec2u getSize() const;
    Vec2u getOrigin() const;
    void setOrigin(const Vec2u &origin);
    bool isColliding(const Vec2u origin, const Vec2u size);

private:
    Vec2u _origin;
    Vec2u _size;
};

#endif /* Collidable_HPP */
