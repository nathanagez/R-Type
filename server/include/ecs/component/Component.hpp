#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <string>

#include "ecs/component/IComponent.hpp"

class Component : public IComponent {
public:
    Component(const ComponentType &type);
    virtual ~Component();

    virtual ComponentType getType() const;

    static std::string getComponentString(const ComponentType &type);
    static ComponentType getComponentType(const std::string &string);

private:
    ComponentType _type;
};

#endif /* COMPONENT_HPP */
