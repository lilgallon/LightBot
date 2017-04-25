#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include "Theme.h"

#include "Utils.h"

class Button
{
public:
    /** CONSTRUCTORS / DESCTRUCTORS **/
    Button(const Utils::State &stateIfClicked,const sf::Vector2f &position, const sf::Vector2f &size, Theme* theme);
    Button(int action,sf::Vector2f position, sf::Vector2f size, Theme* theme);
    ~Button() = default;

    /** GETTERS **/
    bool isOverRect(const sf::Vector2i &mouse) const;
    sf::RectangleShape getButton() const;
    Theme* getTheme() const;
    Utils::State getState() const;
    int getAction() const;

    /** SETTERS **/
    void setColor(const sf::Color &color);
    void setOutlineColor(const sf::Color &color);
    void setTexture(sf::Texture *texture);
    void setLabelText(const std::string &label);
    void setLabelColor(const sf::Color &color);

    /** OTHERS **/
    void draw_on(sf::RenderWindow &window) const;

private:
    void initButton(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor, int outline, sf::Color outlineColor);
    void initLabel(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Text text);

    const Utils::State m_state;
    const int m_action;
    Theme* m_theme;

    sf::RectangleShape m_button;
    sf::Text m_label;
};

#endif // BUTTON_H
