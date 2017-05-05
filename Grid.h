#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"

class Grid
{
public:
    /** CONSTRUCTORS / DESTRUCTORS **/
    Grid(std::vector<Cell *> cells);
    Grid();
    ~Grid();

    /** SETTER **/
    void setGrid(std::vector<Cell*> cells);

    /** GETTERS **/
    std::vector<Cell*> getGrid();
    bool isOverCell(sf::Vector2i mouse);

    /** OTHERS **/
    void drawGrid(sf::RenderWindow& window);

    /** FILE STREAM **/
    void loadLevel(int level_id);

private:
    std::vector<Cell*> m_cells;
    int m_radius;
    // Error handler
    bool m_error_drawing;
};

#endif // GRID_H
