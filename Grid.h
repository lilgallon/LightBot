#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"
#include <algorithm>

class Grid
{
private:
    std::vector<Cell*> m_grid;
public:
    Grid(std::vector<Cell *> grid);
    ~Grid();

    void drawGrid(sf::RenderWindow& window);
    void setGrid(std::vector<Cell*> grid);
    std::vector<Cell*> getGrid();
};

#endif // GRID_H
