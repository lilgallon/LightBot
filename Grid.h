#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"

class Grid
{
private:
    std::vector<Cell*> m_grid;
    int m_radius;
public:
    Grid(std::vector<Cell *> grid);
    ~Grid();

    void drawGrid(sf::RenderWindow& window);
    void setGrid(std::vector<Cell*> grid);
    std::vector<Cell*> getGrid();
    bool isOverCell(sf::Vector2i mouse);
};

#endif // GRID_H
