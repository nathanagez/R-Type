#include "ecs/system/System.hpp"
#include "util/Utils.hpp"

System::System(const SystemType &type) :
    _type(type)
{
}

System::~System()
{
}

SystemType System::getType() const
{
    return (_type);
}

std::string System::getSystemString(const SystemType &type)
{
    switch (type) {
        case 1:
            return ("ARMAMENT");
        case 2:
            return ("COLLISION");
        case 3:
            return ("DAMAGE");
        case 4:
            return ("MOVE");
    }

    return ("UNKNOWN");
}

SystemType System::getSystemType(const std::string &string)
{
    if (Utils::String::isEqualIgnoreCase("ARMAMENT", string))
        return (SystemType::ARMAMENT_SYSTEM);
    if (Utils::String::isEqualIgnoreCase("COLLISION", string))
        return (SystemType::COLLISION_SYSTEM);
    if (Utils::String::isEqualIgnoreCase("DAMAGE", string))
        return (SystemType::DAMAGE_SYSTEM);
    if (Utils::String::isEqualIgnoreCase("MOVE", string))
        return (SystemType::MOVE_SYSTEM);

    return (SystemType::UNKNOWN_SYSTEM);
}
