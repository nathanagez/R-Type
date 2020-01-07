#ifndef DAMAGE_SYSTEM_HPP
#define DAMAGE_SYSTEM_HPP

#include "ecs/system/System.hpp"

class DamageSystem : public System {
public:
    DamageSystem();
    ~DamageSystem();

    void update(const IEntity *entity, const float fElapsedTime) const;
};

#endif /* DAMAGE_SYSTEM_HPP */
