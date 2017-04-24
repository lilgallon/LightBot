#include "Grid.h"

Grid::Grid(std::vector<Cell*> grid)
    :m_grid{grid}
{

}

Grid::~Grid(){
    for(Cell* c : m_grid){
        delete c;
    }
}

void Grid::drawGrid(sf::RenderWindow& window){
    sf::CircleShape hexa;
    hexa.setPointCount(6);
    hexa.setFillColor(sf::Color::Transparent);
    hexa.setOutlineColor(sf::Color::Black);
    hexa.setOutlineThickness(2);
    for(Cell* c : m_grid){
        hexa.setPosition(c->getPos());
        window.draw(hexa);
    }
}

void Grid::setGrid(std::vector<Cell*> grid){
    m_grid = grid;
}

std::vector<Cell*> Grid::getGrid(){
    return m_grid;
}
