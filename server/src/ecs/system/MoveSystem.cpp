#include "ecs/system/MoveSystem.hpp"
#include "ecs/component/Collidable.hpp"
#include "ecs/component/Movable.hpp"
#include "ecs/EntityManager.hpp"
#include "util/Logger.hpp"
#include "util/Utils.hpp"

MoveSystem::MoveSystem() :
    System(SystemType::MOVE_SYSTEM)
{
}

MoveSystem::~MoveSystem()
{
}

void MoveSystem::update(const IEntity *entity, const float fElapsedTime) const
{
    /*** Check if the entity has a Movable component ***/
    IComponent *component = entity->getComponent(ComponentType::MOVABLE_COMPONENT);
    if (!component)
        return;
    auto *movable = dynamic_cast<Movable*>(component);

    /*** Update it's position ***/
    movable->setPosition(Vec2u(
        movable->getPosition().x + movable->getComputedDirection(fElapsedTime).x,
        movable->getPosition().y + movable->getComputedDirection(fElapsedTime).y
    ));

    /*** Check if the entity is still in the window, else destroy the entity ***/
    if (movable->getPosition().x <= 0 || movable->getPosition().x > 1500) {
        EntityManager::getInstance()->destroyEntity(entity->getId());
    }

    /*** Check if the entity has a Collidable component ***/
    component = entity->getComponent(ComponentType::COLLIDABLE_COMPONENT);
    if (!component)
        return;
    auto *collidable = dynamic_cast<Collidable*>(component);

    /*** Update the Collidable component ***/
    collidable->setOrigin(movable->getPosition());
}
