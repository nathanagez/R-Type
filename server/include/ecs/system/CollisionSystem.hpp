#ifndef COLLISION_SYSTEM_HPP
#define COLLISION_SYSTEM_HPP

#include "ecs/system/System.hpp"

class CollisionSystem : public System {
public:
    CollisionSystem();
    ~CollisionSystem();

    void update(const IEntity *entity, const float fElapsedTime) const;
};

#endif /* COLLISION_SYSTEM_HPP */
