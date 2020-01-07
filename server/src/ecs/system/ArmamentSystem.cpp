#include "ecs/system/ArmamentSystem.hpp"
#include "ecs/component/Armed.hpp"
#include "ecs/EntityManager.hpp"
#include "util/Logger.hpp"
#include "util/Utils.hpp"

ArmamentSystem::ArmamentSystem() :
    System(SystemType::ARMAMENT_SYSTEM)
{
}

ArmamentSystem::~ArmamentSystem()
{
}

void ArmamentSystem::update(const IEntity *entity, const float fElapsedTime) const
{
    /*** Check if the entity has an Armed component ***/
    IComponent *component = entity->getComponent(ComponentType::ARMED_COMPONENT);
    if (!component)
        return;
    auto *armed = dynamic_cast<Armed*>(component);

    /*** Update the entity's cooldowns ***/
    armed->updateCooldowns(fElapsedTime);

    /*** Check if the ammunitions are out and cooldown has ended, if true reload them ***/
    if (armed->getAmmunitions() == 0 && armed->getReloadCooldown() <= 0.f)
        armed->reloadAmmunitions();

    /*** Use ammunitions if possible to fire a new Missiles, ***/
    /*** also starts fire rate cooldown after using one or   ***/
    /*** starts reloading cooldown                           ***/
    if (armed->useAmmunitions()) {
        LOG_WARNING("SPAWNER", "missile x1");
        EntityManager::getInstance()->createEntity(armed->getMissileTexture());
    }
}
