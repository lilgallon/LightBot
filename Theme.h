#ifndef THEME_H
#define THEME_H

#include <SFML/Graphics.hpp>

class Theme
{
public:
    /** CONSTRUCTOR **/
    Theme(const int &id);

    /** SETTER **/
    void setTheme(const int &id);

    /** GETTTERS **/

    // Rect default
    sf::Color getRectDefaultFillColor() const;
    sf::Color getRectDefaultOutlineColor() const;
    int getRectOutlineThickness() const;
    // Rect on cursor
    sf::Color getRectOnRectFillColor() const;
    sf::Color getRectOnRectOutlineColor() const;
    // Label
    std::string getLabelText() const;
    sf::Color getLabelDefaultFillColor() const;
    sf::Color getLabelOnRectFillColor() const;
    // Not constant since it modifies m_font and m_text
    sf::Text getLabel();

private:
    // Attributes
    int m_id;
    sf::Font m_font;
    sf::Text m_text;
};

#endif // THEME_H
