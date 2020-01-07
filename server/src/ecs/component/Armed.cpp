#include "ecs/component/Armed.hpp"

Armed::Armed(const unsigned int damage, const unsigned int ammunitions, const float fireRateCooldown, const float reloadCooldown, const std::string &missileTexture) :
    Component(ComponentType::ARMED_COMPONENT),
    _damage(damage),
    _baseAmmunitions(ammunitions),
    _ammunitions(ammunitions),
    _baseFireRateCooldown(fireRateCooldown),
    _baseReloadCooldown(reloadCooldown),
    _missileTexture(missileTexture)
{
}

Armed::~Armed()
{
}

unsigned int Armed::getDamage() const
{
    return (_damage);
}

unsigned int Armed::getBaseAmmunitions() const
{
    return (_baseAmmunitions);
}

unsigned int Armed::getAmmunitions() const
{
    return (_ammunitions);
}

bool Armed::useAmmunitions(const unsigned int ammunitions)
{
    if (!canFire())
        return (false);

    this->_ammunitions -= ammunitions;

    if (_ammunitions <= 0)
        this->_reloadCooldown = _baseReloadCooldown;
    else
        this->_fireRateCooldown = _baseFireRateCooldown;
    return (true);
}

void Armed::reloadAmmunitions()
{
    this->_ammunitions = _baseAmmunitions;
}

float Armed::getBaseFireRateCooldown() const
{
    return (_baseFireRateCooldown);
}

float Armed::getFireRateCooldown() const
{
    return (_fireRateCooldown);
}

float Armed::getBaseReloadCooldown() const
{
    return (_baseReloadCooldown);
}

float Armed::getReloadCooldown() const
{
    return (_reloadCooldown);
}

void Armed::updateCooldowns(float fElapsedTime)
{
    this->_fireRateCooldown -= fElapsedTime;
    this->_reloadCooldown -= fElapsedTime;
}

bool Armed::canFire() const
{
    return (_fireRateCooldown < 0 && _reloadCooldown < 0);
}

std::string Armed::getMissileTexture() const
{
    return (_missileTexture);
}
