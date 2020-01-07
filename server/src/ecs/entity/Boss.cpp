#include "ecs/entity/Boss.hpp"
#include "ecs/component/IComponent.hpp"
#include "ecs/component/Movable.hpp"
#include "serialize.hpp"

Boss::Boss(const std::string &name, const std::string &texture) :
    Entity(EntityType::BOSS_ENTITY, name, texture)
{
}

Boss::~Boss()
{
}

void Boss::init()
{
}

void Boss::update()
{
}

void Boss::serialize(char *buff, const std::string &packet)
{
    Serialize serializer;

    if (packet == "SPAWN") {
        auto *movable = dynamic_cast<Movable*>(getComponent(ComponentType::MOVABLE_COMPONENT));
        serializer.serialize(buff, "UDP_ENTITY_SPAWN_PACKET", GamePacketType::ENTITY_SPAWN,
        this->getId(),
        1280,
        300,
        2,
        0,
        1,
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

