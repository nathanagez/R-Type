#ifndef SETTINGS_SCENE_HPP
#define SETTINGS_SCENE_HPP

#include "Scene.hpp"
#include "Entity.hpp"
#include <SFML/Audio.hpp>
#include "gui/Button.hpp"
#include "gui/Label.hpp"

class SettingsScene : public Scene
{
	public:
		SettingsScene(const std::string &name);

		void onCreate();
		void onDestroy();

		bool onEnable();
		bool onEvent(const sf::Event &event, sf::RenderWindow &window);
		bool onUpdate(const float fElapsedTime);
		bool onRender(sf::RenderWindow &window);
		bool onDisable();
	private:
		Entity background;
		Entity text_input;
		Button::Ptr _back_to_menu;
		Label::Ptr addr_prompt;
		sf::Font font;
		sf::Text addr;
};

#endif /* SETTINGS_SCENE_HPP */
