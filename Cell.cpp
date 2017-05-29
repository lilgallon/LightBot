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

#include "Cell.h"

/************************************************
*                CONSTRUCTOR                    *
*************************************************/
Cell::Cell(const sf::Vector2f &pos, const int &height, const bool &light)
    :m_pos{pos}, m_height{height}, m_light{light}
{
}

/************************************************
*                   SETTERS                     *
*************************************************/
// Sets the height of the Cell (0 - 1 - 2 - ...)
void Cell::setHeight(const int &height){
    m_height = height;
}
// Sets the light of the Cell (true = light is on)
void Cell::setLight(const bool &light){
    m_light = light;
}
// Sets the position of the cell (x,y) in the grid
void Cell::setPos(const sf::Vector2f &pos){
    m_pos = pos;
}

/************************************************
*                   GETTERS                     *
*************************************************/
int Cell::getHeight() const{
    return m_height;
}
bool Cell::getLight() const{
    return m_light;
}
// It returns a Vector2f because it is usefull for the calculations after (no warning)
sf::Vector2f Cell::getPos() const{
    return m_pos;
}



