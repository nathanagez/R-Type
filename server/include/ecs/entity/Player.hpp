#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "ecs/entity/Entity.hpp"

class Player : public Entity {
public:
    Player(const std::string &name);
    ~Player();

    void init();
    void update();
    void serialize(char *buff, const std::string &packet);

private:
};

#endif /* PLAYER_HPP */
