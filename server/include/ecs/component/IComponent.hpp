#ifndef I_COMPONENT_HPP
#define I_COMPONENT_HPP

enum ComponentType {
    UNKNOWN_COMPONENT = 0,
    ARMED_COMPONENT = 1,
    COLLIDABLE_COMPONENT = 2,
    DAMAGEABLE_COMPONENT = 3,
    MOVABLE_COMPONENT = 4
};

class IComponent {
public:
    virtual ComponentType getType() const = 0;
};

#endif /* I_COMPONENT_HPP */
