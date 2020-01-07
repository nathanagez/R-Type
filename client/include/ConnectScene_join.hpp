#ifndef CONNECT_JOIN_SCENE_HPP
#define CONNECT_JOIN_SCENE_HPP

#include "Scene.hpp"
#include "Entity.hpp"
#include "Engine.hpp"
#include "gui/Button.hpp"
#include <iostream>
#include <thread>
#include <future>

class ConnectScene_join : public Scene
{
	public:
		ConnectScene_join(const std::string &name);

		void onCreate();
		void onDestroy();

		bool onEnable();
		bool onEvent(const sf::Event &event, sf::RenderWindow &window);
		bool onUpdate(const float fElapsedTime);
		bool onRender(sf::RenderWindow &window);
		bool onDisable();
		std::string getPlayerName();

		std::string lobby_name;

	private:

		int paralax_offset;
		sf::Font font;

		Entity background;
		Entity text_input;

		Button::Ptr _JoinLobbyList;

		sf::String player1_name;
		sf::Text playerText;
};

#endif /* CONNECT_SCENE_HPP */
