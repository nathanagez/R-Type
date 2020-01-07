#ifndef I_ENTITY_HPP
#define I_ENTITY_HPP

#include <vector>
#include <string>

#include "ecs/component/IComponent.hpp"

enum EntityType {
    UNKNOWN_ENTITY = 0,
    PLAYER_ENTITY = 1,
    MOB_ENTITY = 2,
    BOSS_ENTITY = 3,
    MISSILE_ENTITY = 4
};

class IEntity {
public:
    virtual unsigned int getId() const = 0;
    virtual EntityType getType() const = 0;
    virtual std::string getName() const = 0;
    virtual std::string getTexture() const = 0;
    virtual IComponent *getComponent(const ComponentType &type) const = 0;
    virtual std::vector<IComponent*> getComponents() const = 0;

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void serialize(char *buff, const std::string &packet) = 0;
};

#endif /* I_ENTITY_HPP */
