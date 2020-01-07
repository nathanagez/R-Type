#include "ecs/component/Damageable.hpp"

Damageable::Damageable(const unsigned int hp, const unsigned int reward) :
    Component(ComponentType::DAMAGEABLE_COMPONENT),
    _baseHp(hp),
    _hp(hp),
    _reward(reward)
{
}

Damageable::~Damageable()
{
}

unsigned int Damageable::getBaseHp() const
{
    return (_baseHp);
}

unsigned int Damageable::getHp() const
{
    return (_hp);
}

void Damageable::addHp(const unsigned int hp)
{
    this->_hp += hp;
}

void Damageable::removeHp(const unsigned int hp)
{
    this->_hp -= hp;
}

bool Damageable::isAlive() const
{
    return (_hp);
}

unsigned int Damageable::getReward() const
{
    return (_reward);
}
