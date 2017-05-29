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
    const std::string  FONT_NAME = "coolvetica.ttf";

    const sf::Vector2f ACTION_SIZE = {70,70};
    const sf::Vector2f ACTION_GAP = {2,2};

    const sf::Color    TEXT_COLOR   = sf::Color(128,128,128);
    const sf::Vector2f TEXT_POS_GAP = {0,-35};
}

ProgramBox::ProgramBox(const sf::Vector2f &pos, const sf::Vector2f &size, const sf::Color &fill_color, const sf::Color &outline_color, const int &outline_size, const std::string &prog_name, const Utils::TypeProg &type_prog)
    :m_type_prog{type_prog}
{
    // Inits the box where the actions will be in
    m_rect.setPosition(pos);
    m_rect.setSize(size);
    m_rect.setFillColor(fill_color);
    m_rect.setOutlineColor(outline_color);
    m_rect.setOutlineThickness(outline_size);

    // Inits the text indicating the name of the prog
    // Font load
    if (!m_font.loadFromFile(Utils::FONT_PATH+FONT_NAME)) {
        std::cout << Utils::getTime() + "[Program Box-ERROR]: Could not load the font" << std::endl;
        std::cout << Utils::getTime() + "[Program Box-FIX]: Check \"" + Utils::FONT_PATH+FONT_NAME + "\"" << std::endl;
        std::cout << Utils::getTime() + "[Program Box-FIX]: The font will be ignored." << std::endl;
    }else{
        m_text.setFont(m_font);
        std::cout << Utils::getTime() + "[Program Box-INFO]: Font loaded" << std::endl;
    }

    m_text.setString(prog_name);
    m_text.setColor(TEXT_COLOR);
    m_text.setPosition({TEXT_POS_GAP.x+pos.x,TEXT_POS_GAP.y+pos.y});
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
    // explaination:
    // - To add an action between other actions, we insert the action in the container
    // - We create a copy of this container
    // - We clear the original container
    // - We call the method addAction() for every actions in the copied container


    // Add the action in the container
    m_actions.resize(m_actions.size()+1);
    for(unsigned int i=m_actions.size()-1 ; i>row ; i--){
        m_actions.at(i)=m_actions.at(i-1);
    }
    m_actions.at(row) = action;

    // Create a copy of this container
    std::vector<Button*> temp_container = m_actions;
    // Clear the original container
    m_actions.clear();

    // For every action of the temp container, add the action
    for(Button* b : temp_container){
        addAction(b);
    }
}

void ProgramBox::deleteAction(const unsigned int &row)
{
    // It is the same principe of addAction with a specific row

    if(row>=m_actions.size()){
        std::cout << Utils::getTime() + "[Program Box-ERROR]: An action of row " + std::to_string(row) + " has to be deleted but has not been found" << std::endl;
    }else{
        if(m_actions.at(row)!=nullptr){
            delete m_actions.at(row);
            std::cout << Utils::getTime() + "[Program Box-INFO]: Deleted an action" << std::endl;
        }
        // Left decal
        for(unsigned int i = row; i<=m_actions.size()-2; i++){
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
    // Clear the container (delete all buttons before)

    std::cout << Utils::getTime() + "[Program Box-INFO]: Will clear program box \"" /*+ m_text.getString() + "\"" */<< std::endl;
    for(Button* b : m_actions){
        delete b;
        std::cout << Utils::getTime() + "[Program Box-INFO]: Deleted a button from the program box \"" /*+ m_text.getString() +  "\"" */<< std::endl;
    }
    m_actions.clear();
}

// It calculates the new position of a new action
// if no place was found to add a new action, it returns (-1;-1)
sf::Vector2f ProgramBox::calculateNewPosition() const
{
    // The variables here are for a better comprehension

    float box_pos_x = m_rect.getPosition().x;
    float box_pos_y = m_rect.getPosition().y;

    float box_width = m_rect.getSize().x;
    float box_height = m_rect.getSize().y;

    float action_width = ACTION_SIZE.x;
    float action_heigth = ACTION_SIZE.y;

    float gap_between_actions_width = ACTION_GAP.x;
    float gap_between_actions_height = ACTION_GAP.y;

    float number_of_actions = m_actions.size();

    // max actions on line is determined by the width of the program box, the width of an action, and the gap between those
    float max_actions_on_line = box_width/(gap_between_actions_width+action_width);
    // same for max line but with height
    float max_lines = box_height/(gap_between_actions_height+action_heigth);

    // new_position will not change if no place was found. So no place -> returns {-1;-1}
    sf::Vector2f new_position = {-1,-1};

    float number_of_actions_of_line = number_of_actions;
    // We will begin searching from line 1 (first one)
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
         std::cout << Utils::getTime() + "[Program Box-INFO]: No place found for the action" << std::endl;
    }else{
        // It gets the pos of where we can put the action
        new_position.x = box_pos_x + number_of_actions_of_line*(action_width + gap_between_actions_width);
        if(line==1){
            // If it is the first line, we doesn't apply the Y gap
            new_position.y = box_pos_y + gap_between_actions_height;
        }else{
            new_position.y = box_pos_y + ((line-1)*(action_heigth+gap_between_actions_height));
        }
        // Correct alignemen t (due to button origin set in center)
        new_position.x += action_width/2;
        new_position.y += action_heigth/2;
    }

    return new_position;
}

// Returns true if the mouse is over the program box
bool ProgramBox::overBox(const sf::Vector2i &pos) const
{
    return pos.x >= m_rect.getPosition().x
            && pos.x <= m_rect.getPosition().x + m_rect.getSize().x
            && pos.y >= m_rect.getPosition().y
            && pos.y <= m_rect.getPosition().y + m_rect.getSize().y;
}

/* GETTERS */

std::vector<Button*> ProgramBox::getActions() const
{
    return m_actions;
}

std::string ProgramBox::getName() const
{
    return m_text.getString();
}

Utils::TypeProg ProgramBox::getType() const
{
    return m_type_prog;
}

/* DRAWER */

void ProgramBox::drawProgBox(sf::RenderWindow &window)
{
    window.draw(m_rect);
    for(Button *b : m_actions){
        b->draw_on(window);
    }
    window.draw(m_text);
}
