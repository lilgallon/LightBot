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
const std::string FONT = "ressources/coffee-teademo-Regular.ttf";
}

Button::Button(int id, sf::Vector2f position, sf::Vector2f size, sf::Texture *texture)
    : m_id {id}
{
    //                             the color will be ignored
    initButton(position,size,texture,sf::Color::White);
    initLabel(position,size,"");
}

Button::Button(int id, sf::Vector2f position, sf::Vector2f size, sf::Color color)
    : m_id {id}
{
    initButton(position,size,nullptr,color);
    initLabel(position,size,"");
}

Button::Button(int id, sf::Vector2f position, sf::Vector2f size, sf::Texture *texture, std::string label)
    : m_id {id}
{
    //                             the color will be ignored
    initButton(position,size,texture,sf::Color::White);
    initLabel(position,size,label);
}

Button::Button(int id, sf::Vector2f position, sf::Vector2f size, sf::Color color, std::string label)
    : m_id {id}
{
    initButton(position,size,nullptr,color);
    initLabel(position,size,label);
}

void Button::initLabel( sf::Vector2f position, sf::Vector2f size, std::string label){
    // A TRADUIRE EVIDEMMENT HEIN
    // On vérifie si la police existe, dans ce cas, on affiche
    // le texte. Autrement on indique que la police n'existe pas
    // et on ne charge pas celle-ci pour continuer l'execution
    if (! m_font.loadFromFile(FONT)) {
        //throw "Police "+POLICE+" manquante";
        std::cout << "Font not found, please verify \""
                     + FONT + "\"" << std::endl;
        std::cout << "The font will be ignored." << std::endl;
    }else{
        m_label.setPosition(position);
        m_label.setOrigin(size.x/4,size.y-size.y/2.);
        m_label.setString(label);
        m_label.setColor(sf::Color::Green);
        m_label.setFont(m_font);
        m_label.setCharacterSize(20);
    }
}

void Button::initButton(sf::Vector2f position, sf::Vector2f size, sf::Texture *texture, sf::Color color){
    m_button.setPosition(position);
    m_button.setOrigin(size.x-size.x/2., size.y-size.y/2.);
    m_button.setSize(size);
    if(texture==nullptr){
        m_button.setFillColor(color);
    }else{
        m_button.setTexture(texture);
    }
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
