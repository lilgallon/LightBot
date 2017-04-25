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

#include "Theme.h"
#include "Utils.h"
#include <iostream>

namespace {
    const int FIRST_ID = 1;
    const int LAST_ID = 1;
}

Theme::Theme(int id)
    :m_id{id}
{
    std::cout << Utils::getTime() + "[Theme-INFO]: Loading the theme..." << std::endl;
    if(m_id<FIRST_ID || m_id>LAST_ID){
        std::cout << Utils::getTime() + "[Theme-ERROR]: Invalid theme ID" << std::endl;
        std::cout << Utils::getTime() + "[Theme-FIX]: The theme has been set to default" << std::endl;
        m_id = FIRST_ID;
    }
}

void Theme::setTheme(int id){
    if(m_id<FIRST_ID || m_id>LAST_ID){
        std::cout << Utils::getTime() + "[Theme-ERROR]: Invalid theme ID - Failed to set the theme" << std::endl;
        std::cout << Utils::getTime() + "[Theme-FIX]: Theme set to default" << std::endl;
        m_id = FIRST_ID;
    }else{
        m_id = id;
    }
}


sf::Color Theme::getRectDefaultFillColor(){
    // To prevent any crash if we are in default case
    sf::Color color = sf::Color::Red;
    switch(m_id){
    case 1:
        color = sf::Color::Black;
        break;
    default:
        std::cout << Utils::getTime() + "[Theme-ERROR]: Invalid theme ID from the class" << std::endl;
        break;
    }
    return color;
}

sf::Color Theme::getRectOnRectFillColor(){
    // To prevent any crash if we are in default case
    sf::Color color = sf::Color::Red;
    switch(m_id){
    case 1:
        color = sf::Color::White;
        break;
    default:
        std::cout << Utils::getTime() + "[Theme-ERROR]: Invalid theme ID from the class" << std::endl;
        break;
    }
    return color;
}

sf::Color Theme::getRectDefaultOutlineColor(){
    // To prevent any crash if we are in default case
    sf::Color color = sf::Color::Red;
    switch(m_id){
    case 1:
        color = sf::Color::Blue;
        break;
    default:
        std::cout << Utils::getTime() + "[Theme-ERROR]: Invalid theme ID from the class" << std::endl;
        break;
    }
    return color;
}

sf::Color Theme::getRectOnRectOutlineColor(){
    // To prevent any crash if we are in default case
    sf::Color color = sf::Color::Red;
    switch(m_id){
    case 1:
        color = sf::Color::Red;
        break;
    default:
        std::cout << Utils::getTime() + "[Theme-ERROR]: Invalid theme ID from the class" << std::endl;
        break;
    }
    return color;
}

int Theme::getRectOutlineThickness(){
    // To prevent any crash if we are in  default case
    int thickness = 0;
    switch(m_id){
    case 1:
        thickness = 3;
        break;
    default:
        std::cout << Utils::getTime() + "[Theme-ERROR]: Invalid theme ID from the class" << std::endl;
        break;
    }
    return thickness;
}
/* USELESS TO CHANGE THE TEXT IN THE THEME
std::string Theme::getLabelText(){
    // To prevent any crash if we are in  default case
    std::string text = "";
    switch(m_id){
    case 1:
        text = 3;
        break;
    default:
        std::cout << "[Theme-ERROR]: Invalid theme ID from the class" << std::endl;
        break;
    }
    return thickness;
}
*/

sf::Color Theme::getLabelFillColor(){
    // To prevent any crash if we are in default case
    sf::Color color = sf::Color::Red;
    switch(m_id){
    case 1:
        color = sf::Color::Green;
        break;
    default:
        std::cout << Utils::getTime() + "[Theme-ERROR]: Invalid theme ID from the class" << std::endl;
        break;
    }
    return color;
}

sf::Text Theme::getLabel(){
    // Variables
    std::string fontPath = "ressources/";
    std::string fontName = "";

    // Selection of the font
    switch(m_id){
    case 1:
        fontName = "Ubuntu-L.ttf";
        break;
    default:
        std::cout << Utils::getTime() + "[Theme-ERROR]: Invalid theme ID from the class" << std::endl;
        break;
    }

    // Font load
    if (!m_font.loadFromFile(fontPath+fontName)) {
        //throw "Police "+POLICE+" manquante";
        std::cout << Utils::getTime() + "[Theme-ERROR]: Could not load the font" << std::endl;
        std::cout << Utils::getTime() + "[Theme-FIX]: Check \""
                     + fontPath+fontName + "\"" << std::endl;
        std::cout << Utils::getTime() + "[Theme-FIX]: The font will be ignored." << std::endl;
    }else{
        std::cout << Utils::getTime() + "[Theme-INFO]: Font loaded" << std::endl;
    }

    m_text.setFont(m_font);
    return m_text;
}
