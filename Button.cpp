//    This file is part of LightBot.
//
//    LightBot is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    LightBot is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with LightBot.  If not, see <http://www.gnu.org/licenses/>.

/* LOCAL CLASSES */
#include "Button.h"
#include "Utils.h"

/* LIBRARIES */
#include <iostream>

namespace{
    const int LABEL_SIZE = 20;
}

/************************************************
*                CONSTRUCTORS                   *
*************************************************/
// Constructor for a state button
Button::Button(const Utils::State &stateIfClicked, const sf::Vector2f &position, const sf::Vector2f &size, Theme *theme, const std::string &text)
    : m_state{stateIfClicked}, m_action{Utils::Action::NONE}, m_utility{-1}, m_theme{theme}
{
    std::cout << Utils::getTime() + "[Button-INFO]: Loading button" << std::endl;
    initButton(position,size,theme->getRectDefaultFillColor(),theme->getRectOutlineThickness(),theme->getRectDefaultOutlineColor());
    std::cout << Utils::getTime() + "[Button-INFO]: Surface initialized" << std::endl;
    initLabel(position,size,theme->getLabelDefaultFillColor(),theme->getLabel(),text);
    std::cout << Utils::getTime() + "[Button-INFO]: Label initialized" << std::endl;
}

// Constructor for a button that will start a certain function
Button::Button(const int &utility, const sf::Vector2f &position, const sf::Vector2f &size, Theme *theme, const std::string &text)
    : m_state{Utils::State::IDLE}, m_action{Utils::Action::NONE}, m_utility{utility}, m_theme{theme}
{
    std::cout << Utils::getTime() + "[Button-INFO]: Loading button" << std::endl;
    initButton(position,size,theme->getRectDefaultFillColor(),theme->getRectOutlineThickness(),theme->getRectDefaultOutlineColor());
    std::cout << Utils::getTime() + "[Button-INFO]: Surface initialized" << std::endl;
    initLabel(position,size,theme->getLabelDefaultFillColor(),theme->getLabel(),text);
    std::cout << Utils::getTime() + "[Button-INFO]: Label initialized" << std::endl;
}

// Constructor for an action button
Button::Button(const Utils::Action &action, const sf::Vector2f &position, const sf::Vector2f &size, Theme* theme, const std::string &text)
    :m_state{Utils::State::IDLE}, m_action{action}, m_utility{-1}, m_theme{theme}
{
    std::cout << Utils::getTime() + "[Button-INFO]: Loading button" << std::endl;
    initButton(position,size,theme->getRectDefaultFillColor(),theme->getRectOutlineThickness(),theme->getRectDefaultOutlineColor());
    std::cout << Utils::getTime() + "[Button-INFO]: Surface initialized" << std::endl;
    initLabel(position,size,theme->getLabelDefaultFillColor(),theme->getLabel(), text);
    std::cout << Utils::getTime() + "[Button-INFO]: Label initialized" << std::endl;
}

Button::Button(const Utils::Action &action, const sf::Vector2f &position, const sf::Vector2f &size, Theme* theme)
    :m_state{Utils::State::IDLE}, m_action{action}, m_utility{-1}, m_theme{theme}
{
    std::cout << Utils::getTime() + "[Button-INFO]: Loading button" << std::endl;
    initButton(position,size, theme, action);
    std::cout << Utils::getTime() + "[Button-INFO]: Surface initialized" << std::endl;
}

// Init the label inside a constructor
void Button::initLabel(const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color &color, const sf::Text &font, const std::string &text){

    // Sets the font to the text
    const sf::Font* font1 = font.getFont();
    m_label.setFont(*font1);

    // Sets the label to the text
    m_label.setString(text);

    // Sets the position of the label
    m_label.setOrigin(size.x/3.5,size.y/4.);
    m_label.setPosition(position);

    // Sets the color & size of the label
    m_label.setColor(color);
    m_label.setCharacterSize(LABEL_SIZE);

}
// Init the button insaide a constructor
void Button::initButton(const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color &fillColor, const int &outline, const sf::Color &outlineColor){

    // Sets the size of the rectangle
    m_button.setSize(size);

    // Sets the position of the rectangle
    m_button.setPosition(position);
    m_button.setOrigin(size.x-size.x/2., size.y-size.y/2.);

    // Sets the color / thickness of the rectangle
    m_button.setFillColor(fillColor);
    m_button.setOutlineThickness(outline);
    m_button.setOutlineColor(outlineColor);
}

void Button::initButton(const sf::Vector2f &position, const sf::Vector2f &size, Theme* theme, Utils::Action a){

    // Sets the size of the rectangle
    m_button.setSize(size);

    // Sets the position of the rectangle
    m_button.setPosition(position);
    m_button.setOrigin(size.x-size.x/2., size.y-size.y/2.);

    // Sets the color / thickness of the rectangle according to its theme
    m_button.setFillColor(theme->getRectDefaultFillColor());
    m_button.setOutlineThickness(theme->getRectOutlineThickness());
    m_button.setOutlineColor(theme->getRectDefaultOutlineColor());

    // Set the image name according to the action
    std::string image = "";
    switch (a) {
    case Utils::Action::FORWARD:
        image = "forward.png";
        break;
    case Utils::Action::JUMP:
        image = "jump.png";
        break;
    case Utils::Action::LIGHT:
        image = "light.png";
        break;
    case Utils::Action::TURN_CLOCKWISE:
        image = "clockwise.png";
        break;
    case Utils::Action::TURN_COUNTERCLOCK:
        image = "counterclock.png";
        break;
    case Utils::Action::PROG_P1:
        image = "p1.png";
        break;
    case Utils::Action::PROG_P2:
        image = "p2.png";
        break;
    default:
        break;
    }

    // Load the texture
    if(!m_texture.loadFromFile(Utils::IMG_PATH+image)){
        std::cout << Utils::getTime() + "[TextureAction-ERROR]: Could not load the background" << std::endl;
        std::cout << Utils::getTime() + "[TextureAction-FIX]: Check \"" + Utils::IMG_PATH + "\"" << std::endl;
        std::cout << Utils::getTime() + "[TextureAction-FIX]: The texture will be ignored." << std::endl;
    }else{
        m_button.setTexture(&m_texture);
        std::cout << Utils::getTime() + "[ButtonTexture-INFO]: The texture of the button has been loaded." << std::endl;
    }
}


/************************************************
*                   GETTERS                     *
*************************************************/
// Gets the state designed by the button
Utils::State Button::getState() const{
    return m_state;
}
// Gets the action designed by the button
Utils::Action Button::getAction() const{
    return m_action;
}
// Gets the theme of the button (usefull for onMouse / default colors)
Theme* Button::getTheme() const{
    return m_theme;
}
// Returns true if the position is in the button
bool Button::isOverRect(const sf::Vector2i &mouse) const
{
    return mouse.x >= m_button.getPosition().x - m_button.getSize().x/2
            && mouse.x <= m_button.getPosition().x + m_button.getSize().x - m_button.getSize().x/2
            && mouse.y >= m_button.getPosition().y - m_button.getSize().y/2
            && mouse.y <= m_button.getPosition().y + m_button.getSize().y - m_button.getSize().y/2;
}

std::string Button::getLabelText() const{
    return m_label.getString();
}

sf::Text Button::getLabel() const{
    return m_label;
}

sf::RectangleShape Button::getButton() const{
    return m_button;
}

sf::Texture Button::getTexture() const
{
    return m_texture;
}

int Button::getUtility() const
{
    return m_utility;
}

/************************************************
*                   SETTERS                     *
*************************************************/
// Sets the color of the rectangle
void Button::setColor(const sf::Color &color)
{
    m_button.setFillColor(color);
}
// Sets the outline color of the rectangle
void Button::setOutlineColor(const sf::Color &color){
    m_button.setOutlineColor(color);
}
// Sets the texture of the rectangle
void Button::setTexture(sf::Texture *texture){
    m_button.setTexture(texture);
}
// Sets the text of the rectangle
void Button::setLabelText(const std::string &label){
    m_label.setString(label);
}
void Button::setLabelColor(const sf::Color &color){
    m_label.setColor(color);
}

void Button::setPosition(const sf::Vector2f &pos)
{
    m_button.setPosition(pos);
}

// Sets the theme to the button (changes the colors according to the theme)
void Button::setTheme(Theme *theme)
{
    setColor(theme->getRectDefaultFillColor());
    setLabelColor(theme->getLabelDefaultFillColor());
    setOutlineColor(theme->getRectDefaultOutlineColor());
    m_theme = theme;
}

/************************************************
*                   OTHERS                      *
*************************************************/
// Draws the button on a render window
void Button::draw_on(sf::RenderWindow &window) const
{
    window.draw(m_button);
    window.draw(m_label);

}
