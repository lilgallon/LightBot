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

#include "ProgramBox.h"
#include <iostream>

namespace{
    const std::string FONT_NAME = "resources/fonts/";
}

ProgramBox::ProgramBox(sf::Vector2f pos, sf::Vector2f size, sf::Color fill_color, sf::Color outline_color, int outline_thickness, std::string prog_name)
{
    // Inits the box where the actions will be in
    m_rect.setPosition(pos);
    m_rect.setSize(size);
    m_rect.setFillColor(fill_color);
    m_rect.setOutlineColor(outline_color);
    m_rect.setOutlineThickness(outline_thickness);

    // Inits the text indicating the name of the prog
    // Font load
    if (!m_font.loadFromFile(Utils::FONT_PATH+FONT_NAME)) {
        //throw "Police "+POLICE+" manquante";
        std::cout << Utils::getTime() + "[Program Box-ERROR]: Could not load the font" << std::endl;
        std::cout << Utils::getTime() + "[Program Box-FIX]: Check \""
                     + Utils::FONT_PATH+FONT_NAME + "\"" << std::endl;
        std::cout << Utils::getTime() + "[Program Box-FIX]: The font will be ignored." << std::endl;
    }else{
        std::cout << Utils::getTime() + "[Program Box-INFO]: Font loaded" << std::endl;
    }

    m_text.setFont(m_font);
    m_text.setString(prog_name);
}

ProgramBox::~ProgramBox()
{
    for(Button* b : m_actions){
        delete b;
        std::cout << Utils::getTime() + "[Program Box-INFO]: Deleted a button from a program box" << std::endl;
    }
}

void ProgramBox::addAction(Button* button)
{
    m_actions.push_back(button);
}

void ProgramBox::addAction(Button* action, const unsigned int &row)
{
    m_actions.resize(m_actions.size()+1);
    for(unsigned int i=m_actions.size() ; i>row ; i++){
        m_actions.at(i)=m_actions.at(i-1);
    }
    m_actions.at(row) = action;



 //   m_actions.insert(action,row);
}

void ProgramBox::deleteAction(const unsigned int &row)
{
    if(row>=m_actions.size()){
        std::cout << Utils::getTime() + "[Program Box-ERROR]: An action of row " + std::to_string(row) + " has to be deleted but has not been found" << std::endl;
    }else{
        if(m_actions.at(row)!=nullptr){
             delete m_actions.at(row);
            std::cout << Utils::getTime() + "[Program Box-INFO]: Deleted an action" << std::endl;
        }
        // Left decal
        for(unsigned int i = row; i<m_actions.size()-2; i++){
            m_actions.at(i)=m_actions.at(i+1);
        }
        m_actions.resize(m_actions.size()-1);
    }
}

void ProgramBox::clearActions()
{
    std::cout << Utils::getTime() + "[Program Box-INFO]: Will clear program box \"" /*+ m_text.getString() + "\"" */<< std::endl;
    for(Button* b : m_actions){
        delete b;
        std::cout << Utils::getTime() + "[Program Box-INFO]: Deleted a button from the program box \"" /*+ m_text.getString() +  "\"" */<< std::endl;
    }
    m_actions.clear();
}

std::vector<Button*> ProgramBox::getActions() const
{
    return m_actions;
}

void ProgramBox::drawProgBox(sf::RenderWindow &window)
{
    window.draw(m_rect);
}
