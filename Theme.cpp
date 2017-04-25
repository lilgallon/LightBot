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

/************************************************
*         CONSTRUCTORS / DESTRUCTORS            *
*************************************************/

Theme::Theme(const int &id)
    :m_id{id}
{
    std::cout << Utils::getTime() + "[Theme-INFO]: Loading the theme..." << std::endl;
    if(m_id<FIRST_ID || m_id>LAST_ID){
        std::cout << Utils::getTime() + "[Theme-ERROR]: Invalid theme ID" << std::endl;
        std::cout << Utils::getTime() + "[Theme-FIX]: The theme has been set to default" << std::endl;
        m_id = FIRST_ID;
    }
}

/************************************************
*                SETTERS                        *
*************************************************/
// Sets the theme : All the getters will be influenced by the theme selected (m_id)
void Theme::setTheme(const int &id){
    if(m_id<FIRST_ID || m_id>LAST_ID){
        std::cout << Utils::getTime() + "[Theme-ERROR]: Invalid theme ID - Failed to set the theme" << std::endl;
        std::cout << Utils::getTime() + "[Theme-FIX]: Theme set to default" << std::endl;
        m_id = FIRST_ID;
    }else{
        m_id = id;
    }
}

/************************************************
*                GETTERS                         *
*************************************************/
// Default rect color
sf::Color Theme::getRectDefaultFillColor() const{
    // To prevent any crash if we are in default case
    sf::Color color = sf::Color::Red;
    switch(m_id){
    case 1:
        color = sf::Color(128,128,128);
        break;
    default:
        std::cout << Utils::getTime() + "[Theme-ERROR]: Invalid theme ID from the class" << std::endl;
        break;
    }
    return color;
}
// Mouse on rect color
sf::Color Theme::getRectOnRectFillColor() const{
    // To prevent any crash if we are in default case
    sf::Color color = sf::Color::Red;
    switch(m_id){
    case 1:
        color = sf::Color::Yellow;
        break;
    default:
        std::cout << Utils::getTime() + "[Theme-ERROR]: Invalid theme ID from the class" << std::endl;
        break;
    }
    return color;
}
// Default outline color
sf::Color Theme::getRectDefaultOutlineColor() const{
    // To prevent any crash if we are in default case
    sf::Color color = sf::Color::Red;
    switch(m_id){
    case 1:
        color = sf::Color::Yellow;
        break;
    default:
        std::cout << Utils::getTime() + "[Theme-ERROR]: Invalid theme ID from the class" << std::endl;
        break;
    }
    return color;
}
// Mouse on rect outline color
sf::Color Theme::getRectOnRectOutlineColor() const{
    // To prevent any crash if we are in default case
    sf::Color color = sf::Color::Red;
    switch(m_id){
    case 1:
        color = sf::Color(128,128,128);
        break;
    default:
        std::cout << Utils::getTime() + "[Theme-ERROR]: Invalid theme ID from the class" << std::endl;
        break;
    }
    return color;
}
// Default rect outline thickness
int Theme::getRectOutlineThickness() const{
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
// Default label color
sf::Color Theme::getLabelDefaultFillColor() const{
    // To prevent any crash if we are in default case
    sf::Color color = sf::Color::Red;
    switch(m_id){
    case 1:
        color = sf::Color::Yellow;
        break;
    default:
        std::cout << Utils::getTime() + "[Theme-ERROR]: Invalid theme ID from the class" << std::endl;
        break;
    }
    return color;
}
sf::Color Theme::getLabelOnRectFillColor() const{
    // To prevent any crash if we are in default case
    sf::Color color = sf::Color::Red;
    switch(m_id){
    case 1:
        color = sf::Color(128,128,128);
        break;
    default:
        std::cout << Utils::getTime() + "[Theme-ERROR]: Invalid theme ID from the class" << std::endl;
        break;
    }
    return color;
}
// Default label font (trickshots the SFML bug with fonts
// -> here, the font is loaded in a text, and not directly
// is a font variable which caused an unknown bug
sf::Text Theme::getLabel(){
    // Variables
    std::string fontPath = "ressources/fonts/";
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
