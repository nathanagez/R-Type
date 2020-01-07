#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <memory>
#include <vector>

#include "ecs/entity/IEntity.hpp"
#include "ecs/entity/Entity.hpp"
#include "ecs/entity/Player.hpp"
#include "ecs/entity/Missile.hpp"
#include "lib/DynCaller.hpp"

class EntityManager {
public:
    typedef std::shared_ptr<EntityManager> Ptr;

    static Ptr getInstance();

    ~EntityManager();

    bool hasEntities() const;
    bool hasEnemies() const;
    bool hasPlayers() const;
    IEntity *createPlayer(const std::string &name);
    IEntity *createEntity(const std::string &path);
    IEntity *getEntity(const unsigned int id) const;
    std::vector<IEntity*> getAllEntities() const;
    std::vector<Player*> getPlayers() const;
    std::vector<IEntity*> getEnemies() const;
    std::vector<Missile*> getMissiles() const;
    void destroyEntity(const unsigned int id);
    void clear();

    EntityManager(const EntityManager &other) = delete;
    void operator=(const EntityManager &other) = delete;

private:
    EntityManager() = default;

    static DynCaller _dyn;

    std::vector<IEntity*> _entities;
};

#endif /* ENTITY_MANAGER_HPP */
