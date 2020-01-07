#ifndef LABEL_HPP
#define LABEL_HPP

#include <functional>
#include <string>

#include "gui/Widget.hpp"

class Label : public Widget {
    public:
        typedef std::shared_ptr<Label> Ptr;

        Label();

        static Ptr create(const std::string &text, const std::string &fontPath);

        void handleEvent(sf::RenderWindow &window, const sf::Event &event);
        void draw(sf::RenderWindow &window) const;
        void update(const float fElapsedTime);

        void setPosition(const sf::Vector2f &pos);
        sf::FloatRect getBoundsRect() const;
        void setText(const std::string &text);
        std::string getText() const;
        void setFont(const std::string &fontPath);
        sf::Font getFont() const;
        void setCharacterSize(const unsigned int characterSize);
        unsigned int getCharacterSize() const;
        void setStyle(const sf::Uint32 &style);
        sf::Uint32 getStyle() const;
        void setPadding(const sf::Vector2f &padding);
        sf::Vector2f getPadding() const;
        void setColor(const sf::Color &color);
        sf::Color getColor() const;
        void setHoverColor(const sf::Color &color);
        sf::Color getHoverColor() const;

        void onClick(const std::function<void(Label&)> &callback);

    private:
        sf::Text _text;
        sf::Font _font;
        sf::Color _color;
        sf::Color _hoverColor;
        sf::Vector2f _padding;
        std::function<void(Label&)> _callback;
};

#endif /* LABEL_HPP */
