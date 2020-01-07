#ifndef LIST_HPP
#define LIST_HPP

#include <string>
#include <vector>

#include "gui/Widget.hpp"
#include "gui/Label.hpp"

class List : public Widget {
	public:
		typedef std::shared_ptr<List> Ptr;

		List();

		static Ptr create();

		void handleEvent(sf::RenderWindow &window, const sf::Event &event);
		void draw(sf::RenderWindow &window) const;
		void update(const float fElapsedTime);

		void setPosition(const sf::Vector2f &pos);
		void setSize(const sf::Vector2f &size);
		void setBackgroundColor(const sf::Color &color);
		sf::Color getBackgroundColor() const;
		void setScrollbarColor(const sf::Color &color);
		sf::Color getScrollbarColor() const;

		void addItem(const Label::Ptr &label);
		void clear();
		Label::Ptr getItem(const unsigned int &index);
		std::vector<Label::Ptr> getItems() const;
		bool removeItem(const unsigned int &index);
		void setItems(const std::vector<Label::Ptr> &labels);

		bool hasItems() const;
		unsigned int getItemsCount() const;

	private:
		std::vector<Label::Ptr> _items;
		std::vector<std::string> _itemsTexts;
		sf::RectangleShape _background;
		sf::RectangleShape _scrollbar;
		sf::Vector2u _indexes;
		bool _showScrollbar;
};

#endif /* LIST_HPP */
