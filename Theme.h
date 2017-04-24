#ifndef THEME_H
#define THEME_H

#include <SFML/Graphics.hpp>

class Theme
{
public:
    Theme(int id);
    void setTheme(int id);

    // Ce serait bien avec de la surcharge, de, selon le theme
    // soit changer la couleur, soit changer la texture

    // Rect default
    sf::Color getRectDefaultFillColor();
    sf::Color getRectDefaultOutlineColor();
    // Rect on cursor
    sf::Color getRectOnRectFillColor();
    sf::Color getRectOnRectOutlineColor();


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
