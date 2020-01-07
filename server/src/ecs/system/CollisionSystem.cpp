#include "ecs/system/CollisionSystem.hpp"
#include "ecs/component/IComponent.hpp"
#include "ecs/component/Collidable.hpp"
#include "ecs/entity/IEntity.hpp"
#include "ecs/EntityManager.hpp"
#include "util/Utils.hpp"

CollisionSystem::CollisionSystem() :
    System(SystemType::COLLISION_SYSTEM)
{
}

CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::update(const IEntity *entity, UNUSED const float fElapsedTime) const
{
    /*** Check if the entity is a Missile, we only check Missile collisions ***/
    if (entity->getType() != EntityType::MISSILE_ENTITY)
        return;

    /*** Check if the entity has a Collidable component ***/
    IComponent *component = entity->getComponent(ComponentType::COLLIDABLE_COMPONENT);
    if (!component)
        return;
    auto *collidable = dynamic_cast<Collidable*>(component);

    /*** Loop for each entity to check for collisions ***/
    for (auto *e : EntityManager::getInstance()->getAllEntities()) {
        /*** Check if the entity isn't a Missile, Missiles can't collide themselves ***/
        if (e->getType() == EntityType::MISSILE_ENTITY)
            continue;

        /*** Get the Collidable component of the other element if present, else continue looping ***/
        component = e->getComponent(ComponentType::COLLIDABLE_COMPONENT);
        if (!component)
            continue;
        auto *other = dynamic_cast<Collidable*>(component);

        /*** Check if the entities are colliding ***/
        if (collidable->isColliding(other->getOrigin(), other->getSize())) {
            /*** Destroy both entities ***/
            EntityManager::getInstance()->destroyEntity(entity->getId());
            EntityManager::getInstance()->destroyEntity(e->getId());
        }
    }
}
