#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"
#include "Robot.h"

class Grid
{
public:
    /** CONSTRUCTORS / DESTRUCTORS **/
    Grid(std::vector<Cell *> cells,  Robot* robot);
    Grid();
    ~Grid();

    /** SETTER **/
    void setGrid(std::vector<Cell*> cells);
    void setRobot(Robot* robot);

    /** GETTERS **/
    std::vector<Cell*> getGrid();
    bool isOverCell(sf::Vector2i mouse);
    Cell* getOverCell() const;

    /** OTHERS **/
    void drawGrid(sf::RenderWindow& window);

    /** FILE STREAM **/
    void loadLevel(std::string level_id);
    void saveLevel(std::string level_id, std::string level_name);

private:
    /** INIT **/
    void initLabel();
    void initRobot(const std::__cxx11::string &line);
    //void calculatePosition(Cell* c, sf::Vector2f &pos);

    std::vector<Cell*> m_cells;
    Robot* m_robot;
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
