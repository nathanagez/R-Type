#include "gui/Widget.hpp"

Widget::~Widget()
{
}

sf::Vector2f Widget::getPosition() const
{
    return (_position);
}

void Widget::setPosition(const sf::Vector2f &pos)
{
    this->_position = pos;
}

sf::Vector2f Widget::getSize() const
{
    return (_size);
}

void Widget::setSize(const sf::Vector2f &size)
{
    this->_size = size;
}

bool Widget::isVisible() const
{
    return (_isVisible);
}

void Widget::setVisible(bool visible)
{
    this->_isVisible = visible;
}

bool Widget::isEnabled() const
{
    return (_isEnabled);
}

void Widget::setEnabled(bool enabled)
{
    this->_isEnabled = enabled;
}
