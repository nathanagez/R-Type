#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>
#include <string>

#include <SFML/Audio.hpp>
#include "gui/Widget.hpp"
#include "util/Utils.hpp"

class Button : public Widget {
	public:
		typedef std::shared_ptr<Button> Ptr;

		Button(const std::string &defaultTexturePath, const std::string &pressedTexturePath);

		static Ptr create(const std::string &defaultTexturePath, const std::string &pressedTexturePath, const sf::Vector2f &pos = sf::Vector2f(0.f, 0.f), const std::function<void(Button&)> &callback = [](UNUSED Button &button) {});

		void handleEvent(sf::RenderWindow &window, const sf::Event &event);
		void draw(sf::RenderWindow &window) const;
		void update(const float fElapsedTime);

		void setPosition(const sf::Vector2f &pos);
		void onClick(const std::function<void(Button&)> &callback);

	private:
		sf::Sound _hover_sound;
		sf::SoundBuffer _hover_sound_buffer;
		sf::Texture _defaultTexture;
		sf::Texture _pressedTexture;
		sf::Sprite _sprite;
		std::function<void(UNUSED Button&)> _callback;
};

#endif /* BUTTON_HPP */
