#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <atomic>
#include <string>

#include "ecs/entity/IEntity.hpp"
#include "ecs/component/IComponent.hpp"

class Entity : public IEntity {
public:
    Entity(const EntityType &type, const std::string &name, const std::string &texture);
    virtual ~Entity();

    virtual unsigned int getId() const;
    virtual EntityType getType() const;
    virtual std::string getName() const;
    virtual std::string getTexture() const;
    virtual IComponent *getComponent(const ComponentType &type) const;
    virtual std::vector<IComponent*> getComponents() const;

    virtual void addComponent(IComponent *component);

    static std::string getEntityString(const EntityType &type);
    static EntityType getEntityType(const std::string &string);

private:
    static std::atomic<unsigned int> _entitiesCount;

    unsigned int _id;
    EntityType _type;
    std::string _name;
    std::string _texture;
    std::vector<IComponent*> _components;
};

#endif /* ENTITY_HPP */
