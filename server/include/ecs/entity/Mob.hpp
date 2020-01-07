#ifndef MOB_HPP
#define MOB_HPP

#include "ecs/entity/Entity.hpp"

class Mob : public Entity {
public:
    Mob(const std::string &name, const std::string &texture);
    ~Mob();

    void init();
    void update();
    void serialize(char *buff, const std::string &packet);
};

#endif /* MOB_HPP */
