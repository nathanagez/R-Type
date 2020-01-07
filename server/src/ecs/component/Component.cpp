#include "ecs/component/Component.hpp"
#include "util/Utils.hpp"

Component::Component(const ComponentType &type) :
    _type(type)
{
}

Component::~Component()
{
}

ComponentType Component::getType() const
{
    return (_type);
}

std::string Component::getComponentString(const ComponentType &type)
{
    switch (type) {
        case 1:
            return ("ARMED");
        case 2:
            return ("COLLIDABLE");
        case 3:
            return ("DAMAGEABLE");
        case 4:
            return ("MOVABLE");
    }

    return ("UNKNOWN");
}

ComponentType Component::getComponentType(const std::string &string)
{
    if (Utils::String::isEqualIgnoreCase("ARMED", string))
        return (ComponentType::ARMED_COMPONENT);
    if (Utils::String::isEqualIgnoreCase("COLLIDABLE", string))
        return (ComponentType::COLLIDABLE_COMPONENT);
    if (Utils::String::isEqualIgnoreCase("DAMAGEABLE", string))
        return (ComponentType::DAMAGEABLE_COMPONENT);
    if (Utils::String::isEqualIgnoreCase("MOVABLE", string))
        return (ComponentType::MOVABLE_COMPONENT);

    return (ComponentType::UNKNOWN_COMPONENT);
}
