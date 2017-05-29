#ifndef BUTTON_H
#define BUTTON_H

/* LOCAL CLASSES */
#include "Theme.h"
#include "Utils.h"

/* LIBRARIES */
#include <SFML/Graphics.hpp>

class Button
{
public:
    /** CONSTRUCTORS / DESCTRUCTORS **/
    Button(const Utils::State &stateIfClicked, const sf::Vector2f &position, const sf::Vector2f &size, Theme* theme, const std::string &text);
    Button(const int &utility, const sf::Vector2f &position, const sf::Vector2f &size, Theme* theme, const std::string &text);
    Button(const Utils::Action &action, const sf::Vector2f &position, const sf::Vector2f &size, Theme* theme, const std::string &text);
    Button(const Utils::Action &action, const sf::Vector2f &position, const sf::Vector2f &size, Theme* theme);
    ~Button() = default;

    /** CONSTRUCTOR BY COPY **/
    Button(const Button &b) = default;

    /** GETTERS **/
    bool isOverRect(const sf::Vector2i &mouse) const;
    Theme* getTheme() const;
    Utils::State getState() const;
    Utils::Action getAction() const;
    std::string getLabelText() const;
    sf::Text getLabel() const;
    sf::RectangleShape getButton() const;
    sf::Texture getTexture() const;
    int getUtility() const;

    /** SETTERS **/
    void setColor(const sf::Color &color);
    void setOutlineColor(const sf::Color &color);
    void setTexture(sf::Texture *texture);
    void setLabelText(const std::string &label);
    void setLabelColor(const sf::Color &color);
    void setPosition(const sf::Vector2f &pos);
    void setTheme(Theme* theme);

    /** OTHERS **/
    void draw_on(sf::RenderWindow &window) const;

private:
    // Initialization methods called in contructors (clean the code)
    void initButton(const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color &fillColor, const int &outline, const sf::Color &outlineColor);
    void initLabel(const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color &color, const sf::Text &font, const std::string &text);
    void initButton(const sf::Vector2f &position, const sf::Vector2f &size, Theme *theme, Utils::Action a);

    // Attributes linked to the role of the button:
    // - state: the state to go after clicking the button
    // - action: the action corresponding to the button
    // - utility: the utility of the button to call a method (ex: 1 -> call runProgram, 2 -> call .. and so on)
    const Utils::State m_state;
    const Utils::Action m_action;
    int m_utility;

    // The color theme of the button
    Theme* m_theme;

    // The texture of the button
    sf::Texture m_texture;
    // The rectangle of the button
    sf::RectangleShape m_button;
    // The text of the button
    sf::Text m_label;
};

#endif // BUTTON_H
