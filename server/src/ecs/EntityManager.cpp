#include <algorithm>
#include <cstddef>

#include "ecs/EntityManager.hpp"
#include "ecs/component/Armed.hpp"
#include "ecs/component/Collidable.hpp"
#include "ecs/component/Damageable.hpp"
#include "ecs/component/Movable.hpp"
#include "ecs/entity/IEntity.hpp"
#include "ecs/entity/Player.hpp"
#include "ecs/entity/Boss.hpp"
#include "ecs/entity/Missile.hpp"
#include "ecs/entity/Mob.hpp"

DynCaller EntityManager::_dyn;

EntityManager::Ptr EntityManager::getInstance()
{
    static Ptr instance{new EntityManager};

    return (instance);
}

EntityManager::~EntityManager()
{
    _entities.clear();
}

bool EntityManager::hasEntities() const
{
    return (!_entities.empty());
}

bool EntityManager::hasEnemies() const
{
    for (std::size_t i = 0; i != _entities.size(); i += 1)
        if (_entities[i]->getType() == EntityType::MOB_ENTITY || _entities[i]->getType() == EntityType::BOSS_ENTITY)
            return (true);

    return (false);
}

bool EntityManager::hasPlayers() const
{
    for (std::size_t i = 0; i != _entities.size(); i += 1)
        if (_entities[i]->getType() == EntityType::PLAYER_ENTITY)
            return (true);

    return (false);
}

IEntity *EntityManager::createPlayer(const std::string &name)
{
    Player *player = new Player(name);

    player->addComponent(new Collidable(Vec2u(
        0,
        0
    )));
    player->addComponent(new Damageable(
        200,
        0
    ));
    player->addComponent(new Movable(
        10
    ));

    _entities.push_back(player);

    return (player);
}

IEntity *EntityManager::createEntity(const std::string &path)
{
    std::string type = std::string(_dyn.callMethod<char *>(path, "getType"));
    EntityType entityType = Entity::getEntityType(type);
    std::string name = std::string(_dyn.callMethod<char *>(path, "getName"));
    std::string texture = std::string(_dyn.callMethod<char *>(path, "getTexture"));

    if (entityType == EntityType::MOB_ENTITY) {
        Mob *mob = new Mob(name, texture);

        mob->addComponent(new Armed(
            _dyn.callMethod<unsigned int>(path, "getDamage"),
            _dyn.callMethod<unsigned int>(path, "getAmmunitions"),
            _dyn.callMethod<float>(path, "getFireRate"),
            _dyn.callMethod<float>(path, "getReload"),
            std::string(_dyn.callMethod<char *>(path, "getMissileName"))
        ));
        mob->addComponent(new Collidable(Vec2u(
            _dyn.callMethod<unsigned int>(path, "getSizeX"),
            _dyn.callMethod<unsigned int>(path, "getSizeY")
        )));
        mob->addComponent(new Damageable(
            _dyn.callMethod<unsigned int>(path, "getHp"),
            _dyn.callMethod<unsigned int>(path, "getReward")
        ));
        auto *movable = new Movable(
            _dyn.callMethod<unsigned int>(path, "getSpeed")
        );
        movable->setDirection(Vec2i(
            2,
            0
        ));
        movable->setPosition(Vec2u(
            1280,
            rand() % 673
        ));
        mob->addComponent(movable);

        _entities.push_back(mob);

        return (mob);
    }
    if (entityType == EntityType::BOSS_ENTITY) {
        Boss *boss = new Boss(name, texture);

        boss->addComponent(new Armed(
            _dyn.callMethod<unsigned int>(path, "getDamage"),
            _dyn.callMethod<unsigned int>(path, "getAmmunitions"),
            _dyn.callMethod<float>(path, "getFireRate"),
            _dyn.callMethod<float>(path, "getReload"),
            std::string(_dyn.callMethod<char *>(path, "getMissileName"))
        ));
        boss->addComponent(new Collidable(Vec2u(
            _dyn.callMethod<unsigned int>(path, "getSizeX"),
            _dyn.callMethod<unsigned int>(path, "getSizeY")
        )));
        boss->addComponent(new Damageable(
            _dyn.callMethod<unsigned int>(path, "getHp"),
            _dyn.callMethod<unsigned int>(path, "getReward")
        ));
        boss->addComponent(new Movable(
            _dyn.callMethod<unsigned int>(path, "getSpeed")
        ));

        _entities.push_back(boss);

        return (boss);
    }
    if (entityType == EntityType::MISSILE_ENTITY) {
        Missile *missile = new Missile(name, texture);

        missile->addComponent(new Collidable(Vec2u(
            _dyn.callMethod<unsigned int>(path, "getSizeX"),
            _dyn.callMethod<unsigned int>(path, "getSizeY")
        )));
        missile->addComponent(new Movable(
            _dyn.callMethod<unsigned int>(path, "getSpeed")
        ));

        _entities.push_back(missile);

        return (missile);
    }
    return (nullptr);
}

IEntity *EntityManager::getEntity(const unsigned int id) const
{
    for (std::size_t i = 0; i != _entities.size(); i += 1)
        if (_entities[i]->getId() == id)
            return (_entities[i]);

    return (nullptr);
}

std::vector<IEntity*> EntityManager::getAllEntities() const
{
    return (_entities);
}

std::vector<Player*> EntityManager::getPlayers() const
{
    std::vector<Player*> players;

    for (std::size_t i = 0; i != _entities.size(); i += 1)
        if (_entities[i]->getType() == EntityType::PLAYER_ENTITY)
            players.push_back(dynamic_cast<Player*>(_entities[i]));

    return (players);
}

std::vector<IEntity*> EntityManager::getEnemies() const
{
    std::vector<IEntity*> entities;

    for (std::size_t i = 0; i != _entities.size(); i += 1)
        if (_entities[i]->getType() == EntityType::MOB_ENTITY || _entities[i]->getType() == EntityType::BOSS_ENTITY)
            entities.push_back(_entities[i]);

    return (entities);
}

std::vector<Missile*> EntityManager::getMissiles() const
{
    std::vector<Missile*> missiles;

    for (std::size_t i = 0; i != _entities.size(); i += 1)
        if (_entities[i]->getType() == EntityType::MISSILE_ENTITY)
            missiles.push_back(dynamic_cast<Missile*>(_entities[i]));

    return (missiles);
}

void EntityManager::destroyEntity(const unsigned int id)
{
    _entities.erase(std::remove_if(_entities.begin(), _entities.end(),
       [id](IEntity* e) {
             return (id == e->getId());
     }), _entities.end());
}

void EntityManager::clear()
{
    _entities.clear();
    _dyn.clearCache();
}
