#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include "Theme.h"

#include "Utils.h"

class Button
{
public:
    sf::RectangleShape button();
    void draw_on(sf::RenderWindow &window);
    bool isOverRect(sf::Vector2i mouse);
    void setColor(sf::Color color);
    void setOutlineColor(sf::Color color);
    void setTexture(sf::Texture *texture);
    void setLabelText(std::string label);
    Theme* getTheme();
    Utils::State getState();

    Button(Utils::State stateIfClicked,sf::Vector2f position, sf::Vector2f size, Theme* theme);
    //~Button();

private:
    void initButton(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor, int outline, sf::Color outlineColor);
    void initLabel(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Text text);

    sf::RectangleShape m_button;
    sf::Text m_label;
    Theme* m_theme;
    Utils::State m_state;
};

#endif // BUTTON_H
