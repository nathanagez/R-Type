#include "gui/Button.hpp"
#include "util/Utils.hpp"

Button::Button(const std::string &defaultTexturePath, const std::string &pressedTexturePath) :
	Widget()
{
	while (!this->_defaultTexture.loadFromFile(defaultTexturePath)) {
	}
	this->_defaultTexture.setSmooth(true);

	while (!this->_pressedTexture.loadFromFile(pressedTexturePath)) {
	}
	this->_pressedTexture.setSmooth(true);

	this->_sprite.setTexture(_defaultTexture);
	while (!_hover_sound_buffer.loadFromFile("assets/button_hover.wav")) {
	}
	_hover_sound.setBuffer(_hover_sound_buffer);
}

Button::Ptr Button::create(const std::string &defaultTexturePath, const std::string &pressedTexturePath, const sf::Vector2f &pos, const std::function<void(Button&)> &callback)
{
	auto widget = std::make_shared<Button>(defaultTexturePath, pressedTexturePath);

	widget->setPosition(pos);
	sf::Vector2u size = widget->_sprite.getTexture()->getSize();
	widget->setSize(sf::Vector2f(size.x, size.y));
	widget->onClick(callback);

	return (widget);
}

void Button::handleEvent(sf::RenderWindow &window, const sf::Event &event)
{
	const sf::Texture* prev_texture =_sprite.getTexture();
	if (_sprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
		_sprite.setTexture(_pressedTexture);
	} else {
		_sprite.setTexture(_defaultTexture);
	}
	if (_sprite.getTexture() != prev_texture) {
		_hover_sound.play();
	}
	if (event.type == sf::Event::MouseButtonPressed)
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			if (_sprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				_callback(*this);
}

void Button::draw(sf::RenderWindow &window) const
{
	window.draw(_sprite);
}

void Button::update(UNUSED const float fElapsedTime)
{
}

void Button::setPosition(const sf::Vector2f &pos)
{
	Widget::setPosition(pos);

	_sprite.setPosition(pos);
}

void Button::onClick(const std::function<void(Button&)> &callback)
{
	if (callback)
		this->_callback = callback;
}
