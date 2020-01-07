#ifndef GUI_HPP
#define GUI_HPP

#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Widget.hpp"

class Gui {
    public:
        typedef std::shared_ptr<Gui> Ptr;

        static Ptr getInstance();

        ~Gui();

        void handleEvent(sf::RenderWindow &window, const sf::Event &event);
        void draw(sf::RenderWindow &window);
        void update(const float fElapsedTime);

        bool hasWidgets() const;
        void clear();
        bool addWidget(const Widget::Ptr &widget, const std::string &name);
        Widget::Ptr getWidget(const std::string &name) const;

        Gui(const Gui &other) = delete;
        void operator=(const Gui &other) = delete;

    private:
        Gui() = default;

        std::vector<Widget::Ptr> _widgets;
        std::vector<std::string>  _widgetsNames;
};

#endif /* GUI_HPP */
