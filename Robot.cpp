#include "Robot.h"
#include <iostream>

Robot::Robot(sf::Vector2i pos, Utils::Orientation orientation)
    :m_pos{pos},m_orientation{orientation}
{

}

sf::Vector2i Robot::getPos() const
{
    return m_pos;
}

Utils::Orientation Robot::getOrientation() const
{
    return m_orientation;
}

void Robot::setPos(const sf::Vector2i &pos)
{
    m_pos = pos;
}

void Robot::setOrientation(const Utils::Orientation &orientation)
{
    m_orientation = orientation;
}
