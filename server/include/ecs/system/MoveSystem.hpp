#ifndef MOVE_SYSTEM_HPP
#define MOVE_SYSTEM_HPP

#include "ecs/system/System.hpp"

class MoveSystem : public System {
public:
    MoveSystem();
    ~MoveSystem();

    void update(const IEntity *entity, const float fElapsedTime) const;
};

#endif /* MOVE_SYSTEM_HPP */
