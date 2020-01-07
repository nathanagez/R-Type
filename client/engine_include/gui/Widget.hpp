#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <memory>

#include <SFML/Graphics.hpp>

class Widget {
    public:
        typedef std::shared_ptr<Widget> Ptr;

        virtual ~Widget();

        virtual void handleEvent(sf::RenderWindow &window, const sf::Event &event) = 0;
        virtual void draw(sf::RenderWindow &window) const = 0;
        virtual void update(const float fElapsedTime) = 0;

        sf::Vector2f getPosition() const;
        virtual void setPosition(const sf::Vector2f &pos);
        sf::Vector2f getSize() const;
        virtual void setSize(const sf::Vector2f &size);
        bool isVisible() const;
        virtual void setVisible(bool visible);
        bool isEnabled() const;
        virtual void setEnabled(bool enabled);

    protected:
        sf::Vector2f _position;
        sf::Vector2f _size;
        bool _isVisible;
        bool _isEnabled;
};

#endif /* WIDGET_HPP */
