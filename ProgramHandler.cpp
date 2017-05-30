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
//    Authors : Lilian Gallon, Tristan Renaudon

#include "ProgramHandler.h"
#include <iostream>

// Move the robot forward and returns the "state" of the robot
// with magic numbers
// RESULT ->
// -4 = ALL CELLS ARE NOT TURNED ON
// -3 = FAILED (cell way too high)
// -2 = FAILED (had to jump)
// -1 = FAILED (out of the grid)
// 0 = IT'S FINE FOR THE MOMENT (MAIN)
// 1 = IT'S FINE FOR THE MOMENT (PROGRAM 1)
// 2 = IT'S FINE FOR THE MOMENT (PROGRAM 2)
int ProgramHandler::moveForward(int result)
{
    // Init the new pos at the current robot position
    sf::Vector2i new_pos = {m_robot->getPos().x,m_robot->getPos().y};

    // Move the robot pos according to it's orientation
    switch (m_robot->getOrientation()) {
    case Utils::Orientation::DOWN:
        new_pos.y ++;
        break;
    case Utils::Orientation::DOWN_LEFT:
        if(new_pos.x%2!=0){
            new_pos.x --;
        }else{
            new_pos.x --;
            new_pos.y ++;
        }
        break;
    case Utils::Orientation::DOWN_RIGHT:
        if(new_pos.x%2!=0){
            new_pos.x ++;
        }else{
            new_pos.x ++;
            new_pos.y ++;
        }
        break;
    case Utils::Orientation::UP:
        new_pos.y --;
        break;
    case Utils::Orientation::UP_LEFT:
        if(new_pos.x%2!=0){
            new_pos.x --;
            new_pos.y --;
        }else{
            new_pos.x --;
        }
        break;
    case Utils::Orientation::UP_RIGHT:
        if(new_pos.x%2!=0){
            new_pos.x ++;
            new_pos.y --;
        }else{
            new_pos.x ++;
        }
        break;
    default:
        break;
    }


    // Find final cell (when the robot should go)
    unsigned int i_final = 0;
    bool found_final = false;
    while(!found_final && i_final<m_grid->getGrid().size()){
        if(m_grid->getGrid().at(i_final)->getPos().x==(float)new_pos.x
                && m_grid->getGrid().at(i_final)->getPos().y==(float)new_pos.y){
            found_final = true;
        }else{
            i_final ++;
        }
    }



    if(found_final){
        unsigned int i_init = 0;
        bool found_init = false;

        // Find the cell index where the robot is (initially)
        while(!found_init && i_init<m_grid->getGrid().size()){
            if(m_grid->getGrid().at(i_init)->getPos().x==(float)m_robot->getPos().x
                    && m_grid->getGrid().at(i_init)->getPos().y==(float)m_robot->getPos().y){
                found_init = true;
            }else{
                i_init ++;
            }
        }

        if(!found_init){
            std::cout << "[ProgramHandler-CRITICAL]: Could not find the robot cell (is he dead?)" << std::endl;
        }else{
            // If the final cell height is 1 more that the initial, we have to check if the robot jumped
            if(m_grid->getGrid().at(i_init)->getHeight()==m_grid->getGrid().at(i_final)->getHeight()-1){
                if(m_robot->isJumping()){
                    // OK
                    m_robot->setPos(new_pos);
                }else{
                    // ROBOT DID NOT JUMPED BUT IT HAD TO!!
                    result = -2;
                }
            }else if(m_grid->getGrid().at(i_init)->getHeight()<m_grid->getGrid().at(i_final)->getHeight()){
                // THE FINAL CELL IS WAY TOO HIGH! (dif >1)
                result = -3;
            }else{
                m_robot->setPos(new_pos);
                // The initial cell has an higher or equal height as the final one, the robot can move
            }
        }
    }else{
        // The robot moved in an inexistant cell
        // THE ROBOT HAS TO DIE :)
        result = -1;
    }

    return result;
}

ProgramHandler::ProgramHandler(ProgramBox* program_main, ProgramBox *program_p1, ProgramBox *program_p2, Robot* robot, Grid *grid)
    :m_program_main{program_main}, m_program_p1{program_p1}, m_program_p2{program_p2}, m_robot{robot}, m_grid{grid},m_robot_jumped_before{false}
{}

int ProgramHandler::runProgram(ProgramBox *program, const unsigned int &index, int result, Theme* defaultTheme, Theme* currentActionTheme)
{

    std::vector<Cell *> cells = m_grid->getGrid();

    // The current action has a different theme
    //(like that we know that the robot is doing this action)
    program->getActions().at(index)->setTheme(currentActionTheme);

    // Set default theme to the precedent action (button)
    if(index!=0){
        program->getActions().at(index-1)->setTheme(defaultTheme);
    }

    // We will do things according to the action
    switch (program->getActions().at(index)->getAction()) {
    case Utils::Action::FORWARD:
        result = moveForward(result);
        break;
    case Utils::Action::JUMP:
        m_robot->setJumping(true);
        m_robot_jumped_before = true;
        break;
    case Utils::Action::LIGHT:
        for(Cell* c : cells){
            if(c->getPos().x == m_robot->getPos().x && c->getPos().y == m_robot->getPos().y){
                c->setLight(true);
            }
        }
        break;
    case Utils::Action::TURN_CLOCKWISE:
        m_robot->setOrientation(Utils::turn_clockwise(m_robot->getOrientation()));
        break;
    case Utils::Action::TURN_COUNTERCLOCK:
        m_robot->setOrientation(Utils::turn_counterclock(m_robot->getOrientation()));
        break;
    case Utils::Action::PROG_P1:
        if(program->getType()==Utils::TypeProg::P1){
            std::cout << Utils::getTime() + "[ProgramHandler-INFO]: Infinite loop detected in P1. The instruction causing this loop will be ignored." << std::endl;
        }else{
            // result = 1 -> say that we are running P1
            result = 1;
        }
        break;
    case Utils::Action::PROG_P2:
        if(program->getType()==Utils::TypeProg::P2){
            std::cout << Utils::getTime() + "[ProgramHandler-INFO]: Infinite loop detected in P2. The instruction causing this loop will be ignored." << std::endl;
        }else{
            // result = 2 -> say that we are running P2
            result = 2;
        }
        break;
    default:
        break;
    }

    // If the robot jumped and did go forward after, he lands on the floor
    if(m_robot->isJumping() && program->getActions().at(index)->getAction()==Utils::Action::FORWARD){
        m_robot->setJumping(false);
    }

    return result;
}
