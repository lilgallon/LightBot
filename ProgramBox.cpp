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
    const std::string FONT_NAME = "coolvetica.ttf";
    const sf::Vector2f ACTION_SIZE = {70,70};
    const sf::Vector2f ACTION_GAP = {2,2};
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
    m_text.setColor(sf::Color(128,128,128));
    m_text.setPosition({pos.x,pos.y-35});
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
    sf::Vector2f new_pos = calculateNewPosition();

    if(new_pos.x!=-1){
        Button* copied_button = new Button(button->getAction(),new_pos,ACTION_SIZE,button->getTheme());
        m_actions.push_back(copied_button);
    }
}

void ProgramBox::addAction(Button* action, const unsigned int &row)
{
    // Création copie pointeur
    // TODO
    // ..

    m_actions.resize(m_actions.size()+1);
    for(unsigned int i=m_actions.size()-1 ; i>row ; i--){
        m_actions.at(i)=m_actions.at(i-1);
    }
    m_actions.at(row) = action;


    std::vector<Button*> temp_container = m_actions;
    m_actions.clear();

    for(Button* b : temp_container){
        addAction(b);
    }



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

    std::vector<Button*> temp_container = m_actions;
    m_actions.clear();
    for(Button* b : temp_container){
        addAction(b);
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

sf::Vector2f ProgramBox::calculateNewPosition() const
{
    float box_pos_x = m_rect.getPosition().x;
    float box_pos_y = m_rect.getPosition().y;

    float box_width = m_rect.getSize().x;
    float box_height = m_rect.getSize().y;

    float action_width = ACTION_SIZE.x;
    float action_heigth = ACTION_SIZE.y;

    float gap_between_actions_width = ACTION_GAP.x;
    float gap_between_actions_height = ACTION_GAP.y;

    float number_of_actions = m_actions.size();

    float max_actions_on_line = box_width/(gap_between_actions_width+action_width);
    float max_lines = box_height/(gap_between_actions_height+action_heigth);

    //float line = 1;
    std::cout << std::to_string(max_lines) << std::endl;

    sf::Vector2f new_position = {-1,-1};

    float number_of_actions_of_line = number_of_actions;
    float line = 1;
    bool found = false;

    // It gets the line where it is possible to add an action
    while(line<=max_lines && !found){
        if(max_actions_on_line<=number_of_actions_of_line){
            number_of_actions_of_line -= max_actions_on_line;
            line ++;
        }else{
            found = true;
        }
    }

    if(!found){
        // ON SAIT QUE YA PLUS DE PLACE
         std::cout << Utils::getTime() + "[Program Box-INFO]: No place found for the action" << std::endl;
    }else{
        new_position.x = box_pos_x + number_of_actions_of_line*(action_width + gap_between_actions_width);
        if(line==1){
            // If it is the first line, we doesn't apply the Y gap
            new_position.y = box_pos_y + gap_between_actions_height;
        }else{
            new_position.y = box_pos_y + ((line-1)*(action_heigth+gap_between_actions_height));
        }
        // Correct alignement (due to button origin in center)
        new_position.x += action_width/2;
        new_position.y += action_heigth/2;
    }

    return new_position;
}

bool ProgramBox::overBox(sf::Vector2i pos) const
{
    return pos.x >= m_rect.getPosition().x
            && pos.x <= m_rect.getPosition().x + m_rect.getSize().x
            && pos.y >= m_rect.getPosition().y
            && pos.y <= m_rect.getPosition().y + m_rect.getSize().y;
}

std::vector<Button*> ProgramBox::getActions() const
{
    return m_actions;
}

std::string ProgramBox::getName() const
{
    return m_text.getString();
}

void ProgramBox::drawProgBox(sf::RenderWindow &window)
{
    window.draw(m_rect);
    for(Button *b : m_actions){
        b->draw_on(window);
    }
    window.draw(m_text);
}
