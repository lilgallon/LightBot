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
    void drawGrid(sf::RenderWindow& window, const sf::Vector2f &grid_pos);

    /** FILE STREAM **/
    void loadLevel(const std::string &level_id);
    void saveLevel(const std::string &level_id, const std::string &level_name);

private:
    /** INIT **/
    void initLabel();
    void initRobotRect();
    void initRobot(const std::string &line);

    void changeRobotTexture(Utils::Orientation orientation);
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

    // Texture for the robot
    sf::RectangleShape m_robot_rect;
    sf::Texture m_robot_texture;
    Utils::Orientation m_robot_orientation;

    sf::Vector2f m_gap;
};

#endif // GRID_H
