#ifndef _IPACKETS_H
#define _IPACKETS_H

#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

enum class PacketType
{
	CREATE,
	JOIN,
	LEAVE,
	DELETE,
	START,
	LIST,
	NONE
};

enum class GamePacketType {
	SPAWN,
	ENTITY_SPAWN,
	ENTITY_DESTROY,
	PLAYER_MOVE,
	PLAYER_FIRE
};


// Sent by client
typedef struct ClientTCPPacket
{
	PacketType type;
	uint8_t username[255] {0};
	uint8_t roomId[255] {0};
} ClientTCPPacket_t;

// Sent by server
typedef struct ServerTCPPacket
{
	PacketType type;
	uint8_t lobbies[1024] {0};
	int port;
} ServerTCPPacket_t;

// Send these structs to Robin
typedef struct Player_UDP {
	struct sockaddr_in cliaddr;
	int pos_x;
	int pos_y;
	int dir_x;
	int dir_y;
	uint8_t username[255] {0};
} Player_t;

typedef struct ClientUDPPacket {
	GamePacketType type;
	Player_t me;
} ClientUDPPacket_t;

typedef struct UDPEntity {
	int id;
	int pos_x;
	int pos_y;
	int dir_x;
	int dir_y;
	int speed;
	uint8_t texture[255] {0};
	struct sockaddr_in cliaddr;
} UDPEntity_t;

typedef struct tempPlayer {
	Player_t player1;
	Player_t player2;
	Player_t player3;
	Player_t player4;
} tmpPlayer_t;

typedef struct EntityUDPPacket {
	GamePacketType type;

	// GamePacketType : PLAYER_MOVE
	Player_t player1;
	Player_t player2;
	Player_t player3;
	Player_t player4;

	// GamePacketType : ENTITY_SPAWN
	UDPEntity_t entity;

	// GamePacketType : PLAYER_FIRE
	uint8_t username[255] {0};

	// GamePacketType : ENTITY_DESTROY
	uint8_t entityId;

	// GamePacketType : SPAWN
	Player_t player;

	// After SPAWN
	uint8_t playerList[1024] {0};
} EntityUDPPacket_t;

#endif
