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

#include "Button.h"
#include "Utils.h"
#include <iostream>


/************************************************
*                CONSTRUCTORS                   *
*************************************************/
// Constructor for a state button
Button::Button(const Utils::State &stateIfClicked, const sf::Vector2f &position, const sf::Vector2f &size, Theme *theme, const std::string &text)
    : m_state{stateIfClicked}, m_action{Utils::Action::NONE}, m_theme{theme}
{
    std::cout << Utils::getTime() + "[Button-INFO]: Loading button" << std::endl;
    initButton(position,size,theme->getRectDefaultFillColor(),theme->getRectOutlineThickness(),theme->getRectDefaultOutlineColor());
    std::cout << Utils::getTime() + "[Button-INFO]: Surface initialized" << std::endl;
    initLabel(position,size,theme->getLabelDefaultFillColor(),theme->getLabel(),text);
    std::cout << Utils::getTime() + "[Button-INFO]: Label initialized" << std::endl;
}
// Constructor for an action button
Button::Button(const Utils::Action &action,const sf::Vector2f &position, sf::Vector2f size, Theme* theme, const std::string &text)
    :m_state{Utils::State::IDLE}, m_action{action},m_theme{theme}
{
    std::cout << Utils::getTime() + "[Button-INFO]: Loading button" << std::endl;
    initButton(position,size,theme->getRectDefaultFillColor(),theme->getRectOutlineThickness(),theme->getRectDefaultOutlineColor());
    std::cout << Utils::getTime() + "[Button-INFO]: Surface initialized" << std::endl;
    initLabel(position,size,theme->getLabelDefaultFillColor(),theme->getLabel(), text);
    std::cout << Utils::getTime() + "[Button-INFO]: Label initialized" << std::endl;
}

Button::Button(const Utils::Action &action,const sf::Vector2f &position, sf::Vector2f size, Theme* theme, sf::Texture* texture)
    :m_state{Utils::State::IDLE}, m_action{action},m_theme{theme}, m_texture{texture}
{
    std::cout << Utils::getTime() + "[Button-INFO]: Loading button" << std::endl;
    initButton(position,size, theme, texture);
    std::cout << Utils::getTime() + "[Button-INFO]: Surface initialized" << std::endl;
    //std::cout << Utils::getTime() + "[Button-INFO]: Label initialized" << std::endl;
}


Button::Button(const Button &b)
    :m_state{b.getState()}, m_action {b.getAction()}, m_theme {b.getTheme()}, m_button{b.getButton()}, m_label {b.getLabel()}
{
}
// Init the label inside a constructor
void Button::initLabel(const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color &color, const sf::Text &font, const std::string &text){

    //m_label = font;     // FONT FIX!!

    // marche aussi finalement
    const sf::Font* font1 = font.getFont();
    m_label.setFont(*font1);
    //

    // TODO
    // Améliorer pour prendre en compte la taille du texte pour mieux positionner le label
    m_label.setString(text);
    m_label.setOrigin(size.x/4.5,size.y/4.);
    m_label.setPosition(position);

    m_label.setColor(color);
    m_label.setCharacterSize(20);

}
// Init the button insaide a constructor
void Button::initButton(const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color &fillColor, const int &outline, const sf::Color &outlineColor){
    m_button.setPosition(position);
    m_button.setOrigin(size.x-size.x/2., size.y-size.y/2.);
    m_button.setSize(size);

    m_button.setFillColor(fillColor);
    m_button.setOutlineThickness(outline);
    m_button.setOutlineColor(outlineColor);
    //m_button.setTexture(texture);
}

void Button::initButton(const sf::Vector2f &position, const sf::Vector2f &size, Theme* theme, sf::Texture* texture){
    m_button.setPosition(position);
    m_button.setOrigin(size.x-size.x/2., size.y-size.y/2.);
    m_button.setSize(size);

    m_button.setFillColor(theme->getRectDefaultFillColor());
    m_button.setOutlineThickness(theme->getRectOutlineThickness());
    m_button.setOutlineColor(theme->getRectDefaultOutlineColor());
    m_button.setTexture(texture);
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

/************************************************
*                   OTHERS                      *
*************************************************/
// Draws the button on a render window
void Button::draw_on(sf::RenderWindow &window) const
{
    window.draw(m_button);
    window.draw(m_label);

}
