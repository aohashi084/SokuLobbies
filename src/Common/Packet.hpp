//
// Created by PinkySmile on 30/09/2022.
//

#ifndef SOKULOBBIES_PACKET_HPP
#define SOKULOBBIES_PACKET_HPP


#include <cstdint>
#include <string>

namespace Lobbies
{
	enum Opcode : uint8_t {
		OPCODE_HELLO,
		OPCODE_OLLEH,
		OPCODE_PLAYER_JOIN,
		OPCODE_PLAYER_LEAVE,
		OPCODE_KICKED,
		OPCODE_MOVE,
		OPCODE_POSITION,
		OPCODE_GAME_REQUEST,
		OPCODE_GAME_START,
		OPCODE_PING,
		OPCODE_PONG,
		OPCODE_SETTINGS_UPDATE,
		OPCODE_MESSAGE,
		OPCODE_ARCADE_ENGAGE,
		OPCODE_ARCADE_LEAVE,
		OPCODE_IMPORTANT_MESSAGE,
		OPCODE_INVALID
	};

	enum HostPreference : uint8_t {
		HOSTPREF_CLIENT_ONLY,
		HOSTPREF_HOST_ONLY,
		HOSTPREF_NO_PREF,
		HOSTPREF_HOST_PREF_MASK,
		HOSTPREF_ACCEPT_RELAY
	};

	struct PlayerCustomization {
		uint32_t title;
		uint32_t avatar;
		uint32_t head;
		uint32_t body;
		uint32_t back;
		uint32_t env;
		uint32_t feet;
	};

	struct LobbySettings {
		HostPreference hostPref;
	};

	struct PacketHello {
	private:
		Opcode opcode;

	public:
		char uniqueId[16];
		char name[32];
		PlayerCustomization custom;
		LobbySettings settings;

		PacketHello(char uniqueId[16], const std::string &name, const PlayerCustomization &custom);
		std::string toString() const;
	};

	struct PacketOlleh {
	private:
		Opcode opcode;

	public:
		uint32_t id;
		char realName[64];
		char data[2048]; // This is the lobby customization

		PacketOlleh(const std::string &realName, uint32_t id);
		std::string toString() const;
	};

	struct PacketPlayerJoin {
	private:
		Opcode opcode;

	public:
		uint32_t id;
		char name[64];
		PlayerCustomization custom;

		PacketPlayerJoin(uint32_t id, const std::string &name, PlayerCustomization custom);
		std::string toString() const;
	};

	struct PacketPlayerLeave {
	private:
		Opcode opcode;

	public:
		uint32_t id;

		PacketPlayerLeave(uint32_t id);
		std::string toString() const;
	};

	struct PacketKicked {
	private:
		Opcode opcode;

	public:
		char message[2048];

		PacketKicked(const std::string &msg);
		std::string toString() const;
	};

	struct PacketMove {
	private:
		Opcode opcode;

	public:
		uint32_t id;
		uint8_t dir;

		PacketMove(uint32_t id, uint8_t dir);
		std::string toString() const;
	};

	struct PacketPosition {
	private:
		Opcode opcode;

	public:
		uint32_t id;
		uint32_t x;
		uint32_t y;

		PacketPosition(uint32_t id, uint32_t x, uint32_t y);
		std::string toString() const;
	};

	struct PacketGameRequest {
	private:
		Opcode opcode;

	public:
		uint32_t consoleId;

		PacketGameRequest(uint32_t consoleId);
		std::string toString() const;
	};

	struct PacketGameStart {
	private:
		Opcode opcode;

	public:
		char ip[16];
		uint16_t port;

		PacketGameStart(const std::string &ip, uint16_t port);
		std::string toString() const;
	};

	struct PacketPing {
	private:
		Opcode opcode;

	public:
		PacketPing();
		std::string toString() const;
	};

	struct PacketPong {
	private:
		Opcode opcode;

	public:
		char name[32];
		uint8_t maxPlayers;
		uint8_t currentPlayers;

		PacketPong(const std::string &roomName, uint8_t maxPlayers, uint8_t currentPlayers);
		std::string toString() const;
	};

	struct PacketSettingsUpdate {
	private:
		Opcode opcode;

	public:
		uint32_t id;
		PlayerCustomization custom;
		LobbySettings settings;

		PacketSettingsUpdate(uint32_t id, const PlayerCustomization &custom, const LobbySettings settings);
		std::string toString() const;
	};

	struct PacketMessage {
	private:
		Opcode opcode;

	public:
		uint8_t channelId;
		uint32_t playerId;
		char message[2040];

		PacketMessage(uint8_t channelId, uint32_t playerId, const std::string &message);
		std::string toString() const;
	};

	struct PacketArcadeEngage {
	private:
		Opcode opcode;

	public:
		uint32_t id;

		PacketArcadeEngage(uint32_t id);
		std::string toString() const;
	};

	struct PacketArcadeLeave {
	private:
		Opcode opcode;

	public:
		uint32_t id;

		PacketArcadeLeave(uint32_t id);
		std::string toString() const;
	};

	struct PacketImportantMessage {
	private:
		Opcode opcode;

	public:
		char message[1024];

		PacketImportantMessage(const std::string &msg);
		std::string toString() const;
	};

	union Packet {
		Opcode opcode;
		PacketHello hello;
		PacketOlleh olleh;
		PacketPlayerJoin playerJoin;
		PacketPlayerLeave playerLeave;
		PacketKicked kicked;
		PacketMove move;
		PacketPosition position;
		PacketGameRequest gameRequest;
		PacketGameStart gameStart;
		PacketPing ping;
		PacketPong pong;
		PacketSettingsUpdate settingsUpdate;
		PacketMessage message;
		PacketArcadeEngage arcadeEngage;
		PacketArcadeLeave arcadeLeave;
		PacketImportantMessage importantMsg;

		Packet();
		std::string toString() const;
	};
}


#endif //SOKULOBBIES_PACKET_HPP