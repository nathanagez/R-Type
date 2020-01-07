#include <cstddef>

#include "ecs/SystemManager.hpp"
#include "ecs/system/ArmamentSystem.hpp"
#include "ecs/system/CollisionSystem.hpp"
#include "ecs/system/DamageSystem.hpp"
#include "ecs/system/MoveSystem.hpp"

SystemManager::Ptr SystemManager::getInstance()
{
    static Ptr instance{new SystemManager};

    return (instance);
}

SystemManager::SystemManager()
{
    _systems.push_back(new ArmamentSystem());
    _systems.push_back(new MoveSystem());
    _systems.push_back(new CollisionSystem());
    _systems.push_back(new DamageSystem());
}

SystemManager::~SystemManager()
{
    _systems.clear();
}

bool SystemManager::hasSystems() const
{
    return (!_systems.empty());
}

ISystem *SystemManager::getSystem(const SystemType &type) const
{
    for (std::size_t i = 0; i != _systems.size(); i += 1)
        if (_systems[i]->getType() == type)
            return (_systems[i]);

    return (nullptr);
}

std::vector<ISystem*> SystemManager::getAllSystems() const
{
    return (_systems);
}
