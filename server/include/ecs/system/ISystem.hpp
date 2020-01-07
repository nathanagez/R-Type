#ifndef I_SYSTEM_HPP
#define I_SYSTEM_HPP

#include "ecs/entity/IEntity.hpp"

enum SystemType {
    UNKNOWN_SYSTEM = 0,
    ARMAMENT_SYSTEM = 1,
    COLLISION_SYSTEM = 2,
    DAMAGE_SYSTEM = 3,
    MOVE_SYSTEM = 4
};

class ISystem {
public:
    virtual SystemType getType() const = 0;

    virtual void update(const IEntity *entity, const float fElapsedTime) const = 0;
};

#endif /* I_SYSTEM_HPP */
