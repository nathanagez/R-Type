#ifndef BOSS_HPP
#define BOSS_HPP

#include "ecs/entity/Entity.hpp"

class Boss : public Entity {
public:
    Boss(const std::string &name, const std::string &texture);
    ~Boss();

    void init();
    void update();
    void serialize(char *buff, const std::string &packet);
};

#endif /* BOSS_HPP */
