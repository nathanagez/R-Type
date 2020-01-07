#ifndef MENU_SCENE_HPP
#define MENU_SCENE_HPP

#include "Scene.hpp"

#include <SFML/Audio.hpp>
#include "gui/Button.hpp"

class MenuScene : public Scene
{
	public:
		MenuScene(const std::string &name);

		void onCreate();
		void onDestroy();

		bool onEnable();
		bool onEvent(const sf::Event &event, sf::RenderWindow &window);
		bool onUpdate(const float fElapsedTime);
		bool onRender(sf::RenderWindow &window);
		bool onDisable();
	private:
		sf::Music music;
		sf::Font font;
		sf::Texture background_texture;
		sf::Sprite background_sprite;

		sf::Texture alien_texture;
		sf::Sprite alien_sprite;

		int alien_offset;
		float alien_anim;

		sf::Texture fg_texture;
		sf::Sprite fg_sprite;

		Button::Ptr _startButton;
		Button::Ptr _joinButton;
		Button::Ptr _settingsButton;
		Button::Ptr _quitButton;
};

#endif /* MENU_SCENE_HPP */
