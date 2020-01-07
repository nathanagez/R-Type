#ifndef DAMAGEABLE_HPP
#define DAMAGEABLE_HPP

#include "ecs/component/Component.hpp"

class Damageable : public Component {
public:
    Damageable(const unsigned int hp, const unsigned int reward);
    ~Damageable();

    unsigned int getBaseHp() const;
    unsigned int getHp() const;
    void addHp(const unsigned int hp);
    void removeHp(const unsigned int hp);
    bool isAlive() const;
    unsigned int getReward() const;

private:
    unsigned int _hp;
    unsigned int _baseHp;
    unsigned int _reward;
};

#endif /* DAMAGEABLE_HPP */
