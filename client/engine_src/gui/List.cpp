#include "gui/List.hpp"
#include "util/Logger.hpp"
#include "util/Utils.hpp"

List::List() :
	Widget()
{
}

List::Ptr List::create()
{
	auto widget = std::make_shared<List>();

	widget->setPosition(sf::Vector2f(0, 0));
	widget->setBackgroundColor(sf::Color(180, 180, 180));
	widget->setScrollbarColor(sf::Color(0, 0, 0));

	return (widget);
}

void List::handleEvent(UNUSED sf::RenderWindow &window, UNUSED const sf::Event &event)
{
	if (_items.empty())
		return;

	if (event.type == sf::Event::MouseWheelScrolled) {
		if (_background.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
				if (event.mouseWheelScroll.delta > 0 && _indexes.x != 0)
					_indexes.x -= 1;
				if (event.mouseWheelScroll.delta < 0 && _indexes.y + 1 < _items.size())
					_indexes.x += 1;
			}
		}
	}

	sf::Vector2f offset = _position;
	for (unsigned int i = _indexes.x; i < _items.size(); i += 1) {
		Label::Ptr label =_items[i];

		label->setPosition(offset);
		offset.y += label->getBoundsRect().height;

		if ((_position.y + _size.y) < offset.y) {
			_showScrollbar = true;
			break;
		}

		if (_indexes.x == 0)
			_showScrollbar = false;

		_indexes.y = i;
		label->handleEvent(window, event);
	}
}

void List::update(UNUSED const float fElapsedTime)
{
	if (!_showScrollbar || _items.empty())
		return;

	float unit = (_size.y - 4) / (_items.size() - 1);

	_scrollbar.setSize(sf::Vector2f(
		10.f,
		(_indexes.y - _indexes.x) * unit
	));
	_scrollbar.setPosition(
		_position.x + _size.x - _scrollbar.getSize().x - 2,
		_position.y + _indexes.x * unit + 2
	);
}

void List::draw(UNUSED sf::RenderWindow &window) const
{
	window.draw(_background);

	if (_items.empty())
		return;

	if (_showScrollbar)
		window.draw(_scrollbar);

	for (unsigned int i = _indexes.x; i <= _indexes.y; i += 1)
		_items[i]->draw(window);
}

void List::setPosition(const sf::Vector2f &pos)
{
	Widget::setPosition(pos);

	_background.setPosition(pos);
}

void List::setSize(const sf::Vector2f &size)
{
	Widget::setSize(size);

	_background.setSize(size);
}

void List::setBackgroundColor(const sf::Color &color)
{
	_background.setFillColor(color);
}

sf::Color List::getBackgroundColor() const
{
	return (_background.getFillColor());
}

void List::setScrollbarColor(const sf::Color &color)
{
	_scrollbar.setFillColor(color);
}

sf::Color List::getScrollbarColor() const
{
	return (_scrollbar.getFillColor());
}

void List::addItem(const Label::Ptr &item)
{
	_items.push_back(item);

	sf::FloatRect rect = item->getBoundsRect();
	if (_size.x < rect.width - rect.left)
		_size.x = rect.width - rect.left;
}

void List::clear()
{
	_items.clear();
}

Label::Ptr List::getItem(const unsigned int &index)
{
	return (_items.at(index));
}

std::vector<Label::Ptr> List::getItems() const
{
	return (_items);
}

bool List::removeItem(const unsigned int &index)
{
	if (_items.size() <= index)
		return (false);

    _indexes.x = 0;
    _items.erase(_items.begin() + index);
    return (true);
}

void List::setItems(const std::vector<Label::Ptr> &items)
{
	this->_items = items;
}

bool List::hasItems() const
{
	return (!_items.empty());
}

unsigned int List::getItemsCount() const
{
	return (_items.size());
}
