#include "gui/Label.hpp"
#include "util/Utils.hpp"
#include <iostream>

Label::Label() :
    Widget()
{
}

Label::Ptr Label::create(const std::string &text, const std::string &fontPath)
{
    auto widget = std::make_shared<Label>();

    widget->setText(text);
    widget->setFont(fontPath);
    widget->setPosition(sf::Vector2f(0, 0));
    widget->setPadding(sf::Vector2f(0, 0));
    widget->setColor(sf::Color(0, 0, 0));
    widget->setHoverColor(sf::Color(40, 40, 40));
    widget->onClick([](UNUSED Label &label) {});

    return (widget);
}

void Label::handleEvent(sf::RenderWindow &window, const sf::Event &event)
{
    if (getBoundsRect().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
        _text.setFillColor(_hoverColor);
    else
        _text.setFillColor(_color);

    if (event.type == sf::Event::MouseButtonPressed)
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            if (getBoundsRect().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                _callback(*this);
}

void Label::draw(sf::RenderWindow &window) const
{
    window.draw(_text);
}

void Label::update(UNUSED const float fElapsedTime)
{
}

void Label::setPosition(const sf::Vector2f &pos)
{
    Widget::setPosition(pos);

    _text.setPosition(sf::Vector2f(pos.x + _padding.x, pos.y + _padding.y));
}

sf::FloatRect Label::getBoundsRect() const
{
    sf::FloatRect rect = _text.getGlobalBounds();

    rect.left -= _padding.x;
    rect.top -= _padding.y;
    rect.width += _padding.x * 2;
    rect.height += _padding.y * 2;

    return (rect);
}

void Label::setText(const std::string &text)
{
    _text.setString(text);
}

std::string Label::getText() const
{
    return (_text.getString().toAnsiString());
}

void Label::setFont(const std::string &fontPath)
{
    _font.loadFromFile(fontPath);
    _text.setFont(_font);
}

sf::Font Label::getFont() const
{
    return (_font);
}

void Label::setCharacterSize(const unsigned int characterSize)
{
    _text.setCharacterSize(characterSize);
}

unsigned int Label::getCharacterSize() const
{
    return (_text.getCharacterSize());
}

void Label::setStyle(const sf::Uint32 &style)
{
    _text.setStyle(style);
}

sf::Uint32 Label::getStyle() const
{
    return (_text.getStyle());
}

void Label::setPadding(const sf::Vector2f &padding)
{
    this->_padding = padding;
    _text.setPosition(sf::Vector2f(_position.x + padding.x, _position.y + padding.y));
}

sf::Vector2f Label::getPadding() const
{
    return (_padding);
}

void Label::setColor(const sf::Color &color)
{
    this->_color = color;
}

sf::Color Label::getColor() const
{
    return (_color);
}

void Label::setHoverColor(const sf::Color &color)
{
    this->_hoverColor = color;
}

sf::Color Label::getHoverColor() const
{
    return (_hoverColor);
}

void Label::onClick(const std::function<void(Label&)> &callback)
{
    if (callback)
        this->_callback = callback;
}
