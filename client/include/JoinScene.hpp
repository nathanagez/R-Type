#ifndef JOINSCENE_SCENE_HPP
#define JOINSCENE_SCENE_HPP

#include "Scene.hpp"
#include "Entity.hpp"
#include "Engine.hpp"
#include "gui/Label.hpp"
#include "gui/List.hpp"
#include "gui/Button.hpp"
#include "serialize.hpp"
#include "sockets.hpp"
#include <thread>
#include <future>

class JoinScene : public Scene
{
	public:
		JoinScene(const std::string &name);

		void onCreate();
		void onDestroy();

		bool onEnable();
		bool onEvent(const sf::Event &event, sf::RenderWindow &window);
		bool onUpdate(const float fElapsedTime);
		bool onRender(sf::RenderWindow &window);
		bool onDisable();
		void update_lobby_list(std::string lobby_list_str);
		std::vector<std::string> lobby_vec;

		static std::vector<std::string> split(const std::string &s, char delim);

		bool draw_lobby_list;
		List::Ptr lobby_list;
		std::string lobby_list_str;
	private:
		int paralax_offset;
		sf::Font font;
		Button::Ptr _back_to_menu;
		Entity background;
		Entity Join;
};

#endif /* JOINSCENE_SCENE_HPP */
