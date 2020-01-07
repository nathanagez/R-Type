#include "ecs/system/DamageSystem.hpp"
#include "ecs/component/Damageable.hpp"
#include "util/Utils.hpp"

DamageSystem::DamageSystem() :
    System(SystemType::DAMAGE_SYSTEM)
{
}

DamageSystem::~DamageSystem()
{
}

void DamageSystem::update(UNUSED const IEntity *entity, UNUSED const float fElapsedTime) const
{
    /*** Noop (for now) ***/
}
