#ifndef ARMAMENT_SYSTEM_HPP
#define ARMAMENT_SYSTEM_HPP

#include "ecs/system/System.hpp"

class ArmamentSystem : public System {
public:
    ArmamentSystem();
    ~ArmamentSystem();

    void update(const IEntity *entity, const float fElapsedTime) const;
};

#endif /* ARMAMENT_SYSTEM_HPP */
