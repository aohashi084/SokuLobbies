//
// Created by PinkySmile on 02/10/2022.
//

#ifndef SOKULOBBIES_LOBBYMENU_HPP
#define SOKULOBBIES_LOBBYMENU_HPP


#include <mutex>
#include <thread>
#include <SokuLib.hpp>
#include "Player.hpp"
#include "Socket.hpp"

class Connection;
class LobbyMenu : public SokuLib::IMenu {
private:
	struct Entry {
		std::shared_ptr<Connection> c;
		std::string ip;
		unsigned short port;
		std::string lastName;
		bool first = true;
		std::pair<unsigned, unsigned> lastPlayerCount = {0, 0};
		SokuLib::DrawUtils::Sprite name;
		SokuLib::DrawUtils::Sprite playerCount;
	};
	struct AvatarShowcase {
		unsigned char action = 0;
		unsigned animCtr = 0;
		unsigned anim = 0;
		bool side = false;
	};

	SokuLib::DrawUtils::Sprite title;
	SokuLib::DrawUtils::Sprite ui;
	std::thread _netThread;
	std::thread _connectThread;
	Player _loadedSettings;
	std::mutex _connectionsMutex;
	SokuLib::MenuConnect *_parent;
	int _customCursor = 0;
	unsigned _menuCursor = 0;
	unsigned char _menuState = 0;
	std::vector<std::shared_ptr<Entry>> _connections;
	int _lobbyCtr = 0;
	std::string _lastError;
	Socket _mainServer;
	volatile bool _open = true;
	bool _active = true;
	std::thread _masterThread;
	SokuLib::SWRFont _defaultFont12;
	SokuLib::SWRFont _defaultFont16;
	SokuLib::SWRFont _defaultFont20;
	SokuLib::DrawUtils::Sprite _customizeTexts[3];
	SokuLib::DrawUtils::Sprite _customizeSeat;
	SokuLib::DrawUtils::Sprite _playerName;
	SokuLib::DrawUtils::Sprite _customAvatarName;
	SokuLib::DrawUtils::Sprite _customAvatarRequ;
	SokuLib::DrawUtils::Sprite _loadingText;
	SokuLib::DrawUtils::Sprite _messageBox;
	SokuLib::DrawUtils::Sprite _loadingGear;
	std::vector<AvatarShowcase> _showcases;

	void _netLoop();
	void _masterServerLoop();
	void _connectLoop();
	void _refreshAvatarCustomText();
	void _renderAvatarCustomText();
	void _renderCustomAvatarPreview();

	static bool (LobbyMenu::* const _updateCallbacks[])();
	static void (LobbyMenu::* const _renderCallbacks[])();

	bool _normalMenuUpdate();
	bool _joinLobbyUpdate();
	bool _customizeAvatarUpdate();

	void _dummyRender();
	void _customizeAvatarRender();

public:
	LobbyMenu(SokuLib::MenuConnect *parent);
	~LobbyMenu();
	void _() override;
	int onProcess() override;
	int onRender() override;
	void setActive();
};

#endif //SOKULOBBIES_LOBBYMENU_HPP
