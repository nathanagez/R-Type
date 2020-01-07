#ifndef MISSILE_HPP
#define MISSILE_HPP

#include "ecs/entity/Entity.hpp"

class Missile : public Entity {
public:
    Missile(const std::string &name, const std::string &texture);
    ~Missile();

    void init();
    void update();
    void serialize(char *buff, const std::string &packet);
};

#endif /* MISSILE_HPP */
