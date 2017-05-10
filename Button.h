#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include "Theme.h"

#include "Utils.h"

class Button
{
public:
    /** CONSTRUCTORS / DESCTRUCTORS **/
    Button(const Utils::State &stateIfClicked, const sf::Vector2f &position, const sf::Vector2f &size, Theme* theme, const std::string &text);
    Button(const Utils::Action &action, const sf::Vector2f &position, sf::Vector2f size, Theme* theme, const std::string &text);
    ~Button() = default;

    /** GETTERS **/
    bool isOverRect(const sf::Vector2i &mouse) const;
    sf::RectangleShape getButton() const;
    Theme* getTheme() const;
    Utils::State getState() const;
    Utils::Action getAction() const;
    std::string getLabelText() const;

    /** SETTERS **/
    void setColor(const sf::Color &color);
    void setOutlineColor(const sf::Color &color);
    void setTexture(sf::Texture *texture);
    void setLabelText(const std::string &label);
    void setLabelColor(const sf::Color &color);

    /** OTHERS **/
    void draw_on(sf::RenderWindow &window) const;

private:
    void initButton(const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color &fillColor, const int &outline, const sf::Color &outlineColor);
    void initLabel(const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color &color, const sf::Text &font, const std::string &text);

    const Utils::State m_state;
    const Utils::Action m_action;
    Theme* m_theme;

    sf::RectangleShape m_button;
    sf::Text m_label;
};

#endif // BUTTON_H
