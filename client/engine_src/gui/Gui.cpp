#include <algorithm>
#include <cstddef>

#include "gui/Gui.hpp"
#include "util/Logger.hpp"

Gui::Ptr Gui::getInstance()
{
    static Ptr instance{new Gui};

    return (instance);
}

Gui::~Gui()
{
    _widgets.clear();
    _widgetsNames.clear();
}

void Gui::handleEvent(sf::RenderWindow &window, const sf::Event &event)
{
    for (std::size_t i = 0; i != _widgets.size(); i += 1)
        if (_widgets[i]->isVisible() && _widgets[i]->isEnabled())
            _widgets[i]->handleEvent(window, event);
}

void Gui::draw(sf::RenderWindow &window)
{
    for (const auto &widget : _widgets)
        if (widget->isVisible())
            widget->draw(window);
}

void Gui::update(const float fElapsedTime)
{
    for (std::size_t i = 0; i != _widgets.size(); i += 1)
        if (_widgets[i]->isVisible() && _widgets[i]->isEnabled())
            _widgets[i]->update(fElapsedTime);
}

bool Gui::hasWidgets() const
{
    return (!_widgets.empty());
}

void Gui::clear()
{
    _widgets.clear();
    _widgetsNames.clear();
}

bool Gui::addWidget(const Widget::Ptr &widget, const std::string &name)
{
    if (!widget) {
        LOG_ERROR("Gui", "The widget is null.");
        return (false);
    }
    if (std::find(_widgetsNames.begin(), _widgetsNames.end(), name) != _widgetsNames.end()) {
        LOG_ERROR("Gui", "The widget name \"" + name + "\" is already in use.");
        return (false);
    }

    _widgets.push_back(widget);
    _widgetsNames.push_back(name);

    return (true);
}

Widget::Ptr Gui::getWidget(const std::string &name) const
{
    for (std::size_t i = 0; i != _widgetsNames.size(); i += 1)
        if (_widgetsNames[i] == name)
            return (_widgets[i]);

    return (nullptr);
}
