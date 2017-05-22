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
