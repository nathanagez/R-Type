#ifndef Armed_HPP
#define Armed_HPP

#include <string>

#include "ecs/component/Component.hpp"

class Armed : public Component {
public:
    Armed(const unsigned int damage, const unsigned int ammunitions, const float fireRateCooldown, const float reloadCooldown, const std::string &missileTexture);
    ~Armed();

    unsigned int getDamage() const;
    unsigned int getBaseAmmunitions() const;
    unsigned int getAmmunitions() const;
    bool useAmmunitions(const unsigned int ammunitions = 1);
    void reloadAmmunitions();
    float getBaseFireRateCooldown() const;
    float getFireRateCooldown() const;
    float getBaseReloadCooldown() const;
    float getReloadCooldown() const;
    void updateCooldowns(float fElapsedTime);
    bool canFire() const;
    std::string getMissileTexture() const;

private:
    unsigned int _damage;
    unsigned int _baseAmmunitions;
    unsigned int _ammunitions;
    float _baseFireRateCooldown;
    float _fireRateCooldown;
    float _baseReloadCooldown;
    float _reloadCooldown;
    std::string _missileTexture;
};

#endif /* Armed_HPP */
