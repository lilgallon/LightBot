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
    Cell* getOverCell() const;

    /** OTHERS **/
    void drawGrid(sf::RenderWindow& window);

    /** FILE STREAM **/
    void loadLevel(int level_id);
    void saveLevel(int level_id, std::string level_name);

private:
    /** INIT **/
    void initLabel();

    std::vector<Cell*> m_cells;
    int m_radius;
    // Error handler
    bool m_error_drawing;

    // Only used for the level editor
    sf::Text m_text;
    sf::Font m_font;

    // The cell that is currently on mouse
    Cell* m_over_cell;
};

#endif // GRID_H
