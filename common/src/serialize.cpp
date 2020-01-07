#include <iostream>
#include <cstdarg>
#include <cstring>
#include <arpa/inet.h>
#include "serialize.hpp"
#include "interfaces/IPackets.hpp"

void Serialize::serialize(char *buffer, std::string const args...)
{
	va_list list;
	va_start(list, args);

	if (args == "TCP_CLIENT_PACKET")
	{
		ClientTCPPacket_t clientPacket = {};
		clientPacket.type = va_arg(list, PacketType);
		memcpy(&clientPacket.username, va_arg(list, uint8_t *), sizeof(clientPacket.username));
		memcpy(&clientPacket.roomId, va_arg(list, uint8_t *), sizeof(clientPacket.roomId));
		memcpy(buffer, &clientPacket, va_arg(list, size_t));
	}
	else if (args == "TCP_CLIENT_PACKET_FC")
	{
		ClientTCPPacket_t clientPacket = {};
		clientPacket.type = va_arg(list, PacketType);
		memcpy(&clientPacket.username, va_arg(list, uint8_t *), sizeof(clientPacket.username));
		memset(&clientPacket.roomId, 0, sizeof(ClientTCPPacket_t));
		memcpy(buffer, &clientPacket, va_arg(list, size_t));
	}
	else if (args == "TCP_SERVER_PACKET")
	{
		ServerTCPPacket_t ServerPacket = {};

		ServerPacket.type = va_arg(list, PacketType);
		memcpy(&ServerPacket.lobbies, va_arg(list, uint8_t *), sizeof(ServerPacket.lobbies));
		int port = va_arg(list, int);
		memcpy(&ServerPacket.port, &port, sizeof(ServerPacket.port));
		memcpy(buffer, &ServerPacket, va_arg(list, size_t));
	}
	else if (args == "UDP_CLIENT_PACKET")
	{
		EntityUDPPacket_t clientPacket = {};
		clientPacket.type = va_arg(list, GamePacketType);
		clientPacket.player.pos_x = htons(va_arg(list, int));
		clientPacket.player.pos_y = htons(va_arg(list, int));
		clientPacket.player.dir_x = htons(va_arg(list, int));
		clientPacket.player.dir_y = htons(va_arg(list, int));
		memcpy(&clientPacket.player.username, va_arg(list, uint8_t *), sizeof(clientPacket.player.username));
		memcpy(buffer, &clientPacket, va_arg(list, size_t));
	}
		else if (args == "UDP_ENTITY_SPAWN_PACKET")
	{
		EntityUDPPacket_t EntityPacket = {};

		EntityPacket.type = va_arg(list, GamePacketType);
		EntityPacket.entity.id = htons(va_arg(list, int));
		EntityPacket.entity.pos_x = htons(va_arg(list, int));
		EntityPacket.entity.pos_y = htons(va_arg(list, int));
		EntityPacket.entity.dir_x = htons(va_arg(list, int));
		EntityPacket.entity.dir_y = htons(va_arg(list, int));
		EntityPacket.entity.speed = htons(va_arg(list, int));
		memcpy(&EntityPacket.entity.texture, va_arg(list, uint8_t *), sizeof(EntityPacket.entity.texture));
		memcpy(buffer, &EntityPacket, va_arg(list, size_t));
	}
		else if (args == "UDP_ENTITY_DESTROY_PACKET")
	{
		EntityUDPPacket_t EntityPacket = {};

		EntityPacket.type = va_arg(list, GamePacketType);
		EntityPacket.entityId = htons(va_arg(list, int));
		memcpy(buffer, &EntityPacket, va_arg(list, size_t));
	}
		else if (args == "UDP_PLAYER_MOVE_PACKET")
	{
		EntityUDPPacket_t EntityPacket = {};

		EntityPacket.type = va_arg(list, GamePacketType);
		EntityPacket.player1.pos_x = htons(va_arg(list, int));
		EntityPacket.player1.pos_y = htons(va_arg(list, int));
		EntityPacket.player1.dir_x = htons(va_arg(list, int));
		EntityPacket.player1.dir_y = htons(va_arg(list, int));
		memcpy(&EntityPacket.player1.username, va_arg(list, uint8_t *), sizeof(EntityPacket.player1.username));
		memcpy(buffer, &EntityPacket, va_arg(list, size_t));
	}
		else if (args == "UDP_PLAYER_MOVE_PACKET_SERVER")
	{
		EntityUDPPacket_t EntityPacket = {};

		EntityPacket.type = va_arg(list, GamePacketType);
		EntityPacket.player1.pos_x = htons(va_arg(list, int));
		EntityPacket.player1.pos_y = htons(va_arg(list, int));
		EntityPacket.player1.dir_x = htons(va_arg(list, int));
		EntityPacket.player1.dir_y = htons(va_arg(list, int));
		memcpy(&EntityPacket.player1.username, va_arg(list, uint8_t *), sizeof(EntityPacket.player1.username));
		EntityPacket.player2.pos_x = htons(va_arg(list, int));
		EntityPacket.player2.pos_y = htons(va_arg(list, int));
		EntityPacket.player2.dir_x = htons(va_arg(list, int));
		EntityPacket.player2.dir_y = htons(va_arg(list, int));
		memcpy(&EntityPacket.player2.username, va_arg(list, uint8_t *), sizeof(EntityPacket.player2.username));
		EntityPacket.player3.pos_x = htons(va_arg(list, int));
		EntityPacket.player3.pos_y = htons(va_arg(list, int));
		EntityPacket.player3.dir_x = htons(va_arg(list, int));
		EntityPacket.player3.dir_y = htons(va_arg(list, int));
		memcpy(&EntityPacket.player3.username, va_arg(list, uint8_t *), sizeof(EntityPacket.player3.username));
		EntityPacket.player4.pos_x = htons(va_arg(list, int));
		EntityPacket.player4.pos_y = htons(va_arg(list, int));
		EntityPacket.player4.dir_x = htons(va_arg(list, int));
		EntityPacket.player4.dir_y = htons(va_arg(list, int));
		memcpy(&EntityPacket.player4.username, va_arg(list, uint8_t *), sizeof(EntityPacket.player4.username));
		memcpy(buffer, &EntityPacket, va_arg(list, size_t));
	}
			else if (args == "UDP_PLAYERS_PACKET")
	{
		EntityUDPPacket_t EntityPacket = {};

		memcpy(&EntityPacket.playerList, va_arg(list, uint8_t *), sizeof(EntityPacket.playerList));
		memcpy(buffer, &EntityPacket, va_arg(list, size_t));
	}
		else if (args == "UDP_PLAYER_FIRE_PACKET")
	{
		EntityUDPPacket_t EntityPacket = {};

		EntityPacket.type = va_arg(list, GamePacketType);
		memcpy(&EntityPacket.username, va_arg(list, uint8_t *), sizeof(EntityPacket.username));
		memcpy(buffer, &EntityPacket, va_arg(list, size_t));
	}
	va_end(list);
}

void Serialize::deserialize(char *buffer, void *stru, std::string const &type)
{
	if (type == "TCP_CLIENT_PACKET")
	{
		memcpy(stru, buffer, sizeof(ClientTCPPacket_t));
	}
	else if (type == "TCP_SERVER_PACKET")
	{
		memcpy(stru, buffer, sizeof(ServerTCPPacket_t));
	}
	else if (type == "TCP_CLIENT_PACKET_FC") {
		memcpy(stru, buffer, sizeof(ClientTCPPacket_t));
	} else if (type == "UDP_CLIENT_PACKET") {
		memcpy(stru, buffer, sizeof(EntityUDPPacket_t));
	} else if (type == "UDP_PLAYER_FIRE_PACKET") {
		memcpy(stru, buffer, sizeof(EntityUDPPacket_t));
	}
}
