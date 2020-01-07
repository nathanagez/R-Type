#include <cstddef>

#include "ecs/entity/Entity.hpp"
#include "util/Utils.hpp"

std::atomic<unsigned int> Entity::_entitiesCount = ATOMIC_VAR_INIT(0);

Entity::Entity(const EntityType &type, const std::string &name, const std::string &texture) :
    _type(type),
    _name(name),
    _texture(texture)
{
    this->_id = _entitiesCount;
    _entitiesCount += 1;
}

Entity::~Entity()
{
}

unsigned int Entity::getId() const
{
    return (_id);
}

EntityType Entity::getType() const
{
    return (_type);
}

std::string Entity::getName() const
{
    return (_name);
}

std::string Entity::getTexture() const
{
    return (_texture);
}

IComponent *Entity::getComponent(const ComponentType &type) const
{
    for (std::size_t i = 0; i != _components.size(); i += 1)
        if (_components[i]->getType() == type)
            return (_components[i]);

    return (nullptr);
}

std::vector<IComponent*> Entity::getComponents() const
{
    return (_components);
}

void Entity::addComponent(IComponent *component)
{
    if (!component)
        return;

    _components.push_back(component);
}

std::string Entity::getEntityString(const EntityType &type)
{
    switch (type) {
        case 1:
            return ("PLAYER");
        case 2:
            return ("MOB");
        case 3:
            return ("BOSS");
        case 4:
            return ("MISSILE");
    }

    return ("UNKNOWN");
}

EntityType Entity::getEntityType(const std::string &string)
{
    if (Utils::String::isEqualIgnoreCase("PLAYER", string))
        return (EntityType::PLAYER_ENTITY);
    if (Utils::String::isEqualIgnoreCase("MOB", string))
        return (EntityType::MOB_ENTITY);
    if (Utils::String::isEqualIgnoreCase("BOSS", string))
        return (EntityType::BOSS_ENTITY);
    if (Utils::String::isEqualIgnoreCase("MISSILE", string))
        return (EntityType::MISSILE_ENTITY);

    return (EntityType::UNKNOWN_ENTITY);
}
