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
                if(c->getPos().x == m_robot->getPos().x
                        && c->getPos().y == m_robot->getPos().y){
                    c->setLight(true);
                }
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
