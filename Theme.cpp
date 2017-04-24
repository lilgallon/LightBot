#include "Theme.h"
#include <iostream>

namespace {
    const int FIRST_ID = 1;
    const int LAST_ID = 1;
}

Theme::Theme(int id)
    :m_id{id}
{
    if(m_id<FIRST_ID || m_id>LAST_ID){
        std::cout << "[Theme-ERROR]: Invalid theme ID" << std::endl;
        std::cout << "[Theme-FIX]: Theme set to default" << std::endl;
        m_id = FIRST_ID;
    }
}

void Theme::setTheme(int id){
    if(m_id<FIRST_ID || m_id>LAST_ID){
        std::cout << "[Theme-ERROR]: Invalid theme ID" << std::endl;
        std::cout << "[Theme-FIX]: Theme set to default" << std::endl;
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
        std::cout << "[Theme-ERROR]: Invalid theme ID from the class" << std::endl;
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
        std::cout << "[Theme-ERROR]: Invalid theme ID from the class" << std::endl;
        break;
    }
    return color;
}

sf::Color Theme::getRectOutlineColor(){
    // To prevent any crash if we are in default case
    sf::Color color = sf::Color::Red;
    switch(m_id){
    case 1:
        color = sf::Color::Blue;
        break;
    default:
        std::cout << "[Theme-ERROR]: Invalid theme ID from the class" << std::endl;
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
        std::cout << "[Theme-ERROR]: Invalid theme ID from the class" << std::endl;
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
        std::cout << "[Theme-ERROR]: Invalid theme ID from the class" << std::endl;
        break;
    }
    return color;
}

sf::Font Theme::getLabelFont(){
    // Variables
    std::string fontPath = "ressources/";
    std::string fontName = "";
    sf::Font font;

    // Selection of the font
    switch(m_id){
    case 1:
        fontName = "Ubuntu-L.ttf";
        break;
    default:
        std::cout << "[Theme-ERROR]: Invalid theme ID from the class" << std::endl;
        break;
    }

    // Font load
    if (!font.loadFromFile(fontPath+fontName)) {
        //throw "Police "+POLICE+" manquante";
        std::cout << "[Theme-ERROR]: Could not load the font" << std::endl;
        std::cout << "[Theme-FIX]: Check \""
                     + fontPath+fontName + "\"" << std::endl;
        std::cout << "[Theme-FIX]: The font will be ignored." << std::endl;
    }else{
        std::cout << "[Theme]: Font loaded" << std::endl;
    }
    return font;
}
