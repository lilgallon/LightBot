#include "Cell.h"

Cell::Cell(sf::Vector2i pos, int height, bool light)
    :m_pos{pos}, m_height{height}, m_light{light}
{

}


void Cell::setHeight(int height){
    m_height = height;
}

void Cell::setLight(bool light){
    m_light = light;
}

void Cell::setPos(sf::Vector2f pos){
    m_pos = pos;
}

int Cell::getHeight(){
    return m_height;
}

bool Cell::getLight(){
    return m_light;
}

sf::Vector2f Cell::getPos(){
    return m_pos;
}

