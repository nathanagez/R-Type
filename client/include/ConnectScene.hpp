#ifndef CONNECT_SCENE_HPP
#define CONNECT_SCENE_HPP

#include "Scene.hpp"
#include "Entity.hpp"
#include "gui/Button.hpp"
#include <future>

class ConnectScene : public Scene
{
	public:
		ConnectScene(const std::string &name);

		void onCreate();
		void onDestroy();
		bool onEnable();
		bool onEvent(const sf::Event &event, sf::RenderWindow &window);
		bool onUpdate(const float fElapsedTime);
		bool onRender(sf::RenderWindow &window);
		bool onDisable();
		std::string getPlayerName();
		void setPlayerName(std::string username);
		static void handleTCP_connection();

		// c = create_lobby
		// l = get_lobby_list
		std::atomic<char> command;

	private:
		int paralax_offset;
		sf::Font font;
		Entity background;
		Entity text_input;

		Button::Ptr _createRoom;

		sf::Texture background_texture;
		sf::Sprite background_sprite;

		sf::String player1_name;
		sf::Text playerText;
};

#endif /* CONNECT_SCENE_HPP */
