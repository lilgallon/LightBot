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

#include "ProgramHandler.h"

void ProgramHandler::moveForward()
{
    // TODO TRAITER LES CAS IMPOSSIBLE X<0, PAS CELL à x et y .., height,..

    switch (m_robot->getOrientation()) {
    case Utils::Orientation::DOWN:
        m_robot->setPos({m_robot->getPos().x-1,m_robot->getPos().y});
        break;
    case Utils::Orientation::DOWN_LEFT:
        m_robot->setPos({m_robot->getPos().x-1,m_robot->getPos().y-1});
        break;
    case Utils::Orientation::DOWN_RIGHT:
        m_robot->setPos({m_robot->getPos().x+1,m_robot->getPos().y-1});
        break;
    case Utils::Orientation::UP:
        m_robot->setPos({m_robot->getPos().x,m_robot->getPos().y+1});
        break;
    case Utils::Orientation::UP_LEFT:
        m_robot->setPos({m_robot->getPos().x-1,m_robot->getPos().y+1});
        break;
    case Utils::Orientation::UP_RIGHT:
        m_robot->setPos({m_robot->getPos().x+1,m_robot->getPos().y+1});
        break;
    default:
        break;
    }
}

ProgramHandler::ProgramHandler(ProgramBox* program, Robot* robot, Grid *grid)
    :m_program{program}, m_robot{robot}, m_robot_jumped{false}, m_grid{grid}
{

}

void ProgramHandler::runProgram()
{
    std::vector<Button*> actions = m_program->getActions();
    std::vector<Cell *> cells = m_grid->getGrid();

    for(Button* action : actions){
        switch (action->getAction()) {
        case Utils::Action::FORWARD:
                moveForward();
            break;
        case Utils::Action::JUMP:
            m_robot_jumped = true;
            break;
        case Utils::Action::LIGHT:
            for(Cell* c : cells){
                // TODO: Verifier si la cellule est à sa hauteur ou moins s'il na pas sauté
                if(c->getPos().x == m_robot->getPos().x
                        && c->getPos().y == m_robot->getPos().y){
                    c->setLight(true);
                }
                // S'il a sauté, vérifier si la cellule est à une hauteur de plus
                // ...

                // TODO -> cell : afficher la hauteur au lieu de l'indice (1;0 ...)
            }
            break;
        case Utils::Action::TURN_CLOCKWISE:

            break;
        case Utils::Action::TURN_COUNTERCLOCK:

            break;
        case Utils::Action::PROG_P1:

            break;
        case Utils::Action::PROG_P2:

            break;
        default:
            break;
        }
    }
}
