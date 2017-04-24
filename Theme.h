#ifndef THEME_H
#define THEME_H

#include <SFML/Graphics.hpp>

class Theme
{
public:
    Theme(int id);
    void setTheme(int id);

    // Rect
    sf::Color getRectDefaultFillColor();
    sf::Color getRectOutlineColor();
    sf::Color getRectOnRectFillColor();
    int getRectOutlineThickness();

    // Label
    std::string getLabelText();
    sf::Color getLabelFillColor();
    sf::Font getLabelFont();

private:
    // Attributes
    int m_id;
};

#endif // THEME_H
