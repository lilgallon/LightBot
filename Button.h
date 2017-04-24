#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include "Theme.h"

class Button
{
public:
    sf::RectangleShape button();
    void draw_on(sf::RenderWindow & window);
    bool overRect(sf::Vector2i mousePos, sf::RectangleShape button);
    void setColor(sf::Color color);
    void setTexture(sf::Texture *texture);
    void setLabel(std::string label);
    Theme* getTheme();
    int getId();

    Button(int buttonId, sf::Vector2f position, sf::Vector2f size, Theme* theme);
    ~Button();

private:
    void initButton(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor, int outline, sf::Color outlineColor);
    void initLabel(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Font font);

    int m_id;
    sf::RectangleShape m_button;
    sf::Text m_label;
    Theme * m_theme;
};

#endif // BUTTON_H
