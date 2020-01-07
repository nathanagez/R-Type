#ifndef LOBBYSCENE_SCENE_HPP
#define LOBBYSCENE_SCENE_HPP

#include "Scene.hpp"
#include "Entity.hpp"
#include "gui/List.hpp"
#include "gui/Label.hpp"
#include "gui/Button.hpp"
#include <thread>
#include <future>

class LobbyScene : public Scene
{
	public:
		LobbyScene(const std::string &name);

		void onCreate();
		void onDestroy();

		bool onEnable();
		bool onEvent(const sf::Event &event, sf::RenderWindow &window);
		bool onUpdate(const float fElapsedTime);
		bool onRender(sf::RenderWindow &window);
		bool onDisable();

		void update_user_list(std::string user_list_str);

		bool created;

		bool draw_user_list;
		List::Ptr _user_list;

		std::vector<sf::Text> player_list;

	private:
		int paralax_offset;
		sf::Font font;

		Entity background;
		Entity lobby;
};

#endif /* LOBBYSCENE_SCENE_HPP */
