#include "ecs/entity/Mob.hpp"
#include "ecs/component/IComponent.hpp"
#include "ecs/component/Movable.hpp"
#include "serialize.hpp"

Mob::Mob(const std::string &name, const std::string &texture) :
    Entity(EntityType::MOB_ENTITY, name, texture)
{
}

Mob::~Mob()
{
}

void Mob::init()
{
}

void Mob::update()
{
}

void Mob::serialize(char *buff, const std::string &packet)
{
        Serialize serializer;

    if (packet == "SPAWN") {
        auto *movable = dynamic_cast<Movable*>(getComponent(ComponentType::MOVABLE_COMPONENT));
        serializer.serialize(buff, "UDP_ENTITY_SPAWN_PACKET", GamePacketType::ENTITY_SPAWN,
        this->getId(),
        movable->getPosition().x,
        movable->getPosition().y,
        movable->getDirection().x,
        movable->getDirection().y,
        movable->getSpeed(),
        this->getTexture().c_str(),
        sizeof(EntityUDPPacket_t)
        );
    } else if (packet == "DESTROY") {
        serializer.serialize(buff, "UDP_ENTITY_DESTROY_PACKET", GamePacketType::ENTITY_DESTROY,
        this->getId(),
        sizeof(EntityUDPPacket_t)
        );
    }
}
