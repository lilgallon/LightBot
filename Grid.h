#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"

class Grid
{
public:
    /** CONSTRUCTORS / DESTRUCTORS **/
    Grid(std::vector<Cell *> grid);
    ~Grid();

    /** SETTER **/
    void setGrid(std::vector<Cell*> grid);

    /** GETTERS **/
    std::vector<Cell*> getGrid();
    bool isOverCell(sf::Vector2i mouse);

    /** OTHERS **/
    void drawGrid(sf::RenderWindow& window);

    /** FILE STREAM **/
    void loadLevel(int level_id);

private:
    std::vector<Cell*> m_grid;
    int m_radius;
};

#endif // GRID_H
