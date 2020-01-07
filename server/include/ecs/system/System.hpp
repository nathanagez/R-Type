#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <string>

#include "ecs/system/ISystem.hpp"
#include "game.hpp"

class System : public ISystem {
public:
    System(const SystemType &type);
    virtual ~System();

    virtual SystemType getType() const;

    static std::string getSystemString(const SystemType &type);
    static SystemType getSystemType(const std::string &string);

private:
    SystemType _type;
};

#endif /* SYSTEM_HPP */
