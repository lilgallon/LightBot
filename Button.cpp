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
#include <iostream>

namespace {
const std::string FONT = "ressources/Travis_Sans_MS.ttf";
}

Button::Button(int buttonId, sf::Vector2f position, sf::Vector2f size, Theme *theme)
    : m_id {buttonId}, m_theme{theme}
{
    initButton(position,size,theme->getRectDefaultFillColor(),theme->getRectOutlineThickness(),theme->getRectOutlineColor());
    initLabel(position,size,theme->getLabelFillColor(),theme->getLabelFont());
}

Button::~Button(){
    delete m_theme;
}

Theme* Button::getTheme(){
    return m_theme;
}

void Button::initLabel( sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Font font){

    //m_label.setPosition(0,0);
    m_label.setPosition(position);
    //m_label.setOrigin(size.x/4,size.y-size.y/2.);
    //m_label.setOrigin(0,0);
    m_label.setString("iyc");
    m_label.setColor(color);
    //m_label.setFont(font);
    //m_label.setFont();
    m_label.setCharacterSize(20);

}

void Button::initButton(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor, int outline, sf::Color outlineColor){
    m_button.setPosition(position);
    m_button.setOrigin(size.x-size.x/2., size.y-size.y/2.);
    m_button.setSize(size);

    m_button.setFillColor(fillColor);
    m_button.setOutlineThickness(outline);
    m_button.setOutlineColor(outlineColor);



    //m_button.setTexture(texture);
}


bool Button::overRect(sf::Vector2i mousePos, sf::RectangleShape button)
{
    return mousePos.x >= button.getPosition().x - button.getSize().x/2
            && mousePos.x <= button.getPosition().x + button.getSize().x - button.getSize().x/2
            && mousePos.y >= button.getPosition().y - button.getSize().y/2
            && mousePos.y <= button.getPosition().y + button.getSize().y - button.getSize().y/2;
}

/******** SETTERS **********/
void Button::setColor(sf::Color color)
{
    m_button.setFillColor(color);
}
void Button::setTexture(sf::Texture *texture){
    m_button.setTexture(texture);
}

void Button::setLabel(std::string label){
    m_label.setString(label);
}

int Button::getId()
{
    return m_id;
}


sf::RectangleShape Button::button()
{
    return m_button;
}

void Button::draw_on(sf::RenderWindow &window)
{
    window.draw(m_button);
    window.draw(m_label);
}
