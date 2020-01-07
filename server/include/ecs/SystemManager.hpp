#ifndef SYSTEM_MANAGER_HPP
#define SYSTEM_MANAGER_HPP

#include <memory>
#include <vector>

#include "ecs/system/ISystem.hpp"
#include "ecs/entity/IEntity.hpp"
#include "ecs/component/IComponent.hpp"

class SystemManager {
public:
    typedef std::shared_ptr<SystemManager> Ptr;

    static Ptr getInstance();

    ~SystemManager();

    bool hasSystems() const;
    ISystem *getSystem(const SystemType &type) const;
    std::vector<ISystem*> getAllSystems() const;

    void manageComponent(IEntity *entity, IComponent *component) const;

    SystemManager(const SystemManager &other) = delete;
    void operator=(const SystemManager &other) = delete;

private:
    SystemManager();

    std::vector<ISystem*> _systems;
};

#endif /* SYSTEM_MANAGER_HPP */
