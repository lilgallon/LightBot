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

    void changeRobotTexture(const Utils::Orientation &orientation);

    // All the cells of the grid
    std::vector<Cell*> m_cells;
    // The robot
    Robot* m_robot;

    // Radius of the hexagones
    int m_radius;
    // Gap of the grid in the window
    sf::Vector2f m_gap;

    // Error handler (prevent from spamming it in the console)
    bool m_error_drawing;

    // Only used for the level editor
    sf::Text m_text;
    sf::Font m_font;

    // The cell that is currently on mouse
    Cell* m_over_cell;


    // Rectangle of the robot
    sf::RectangleShape m_robot_rect;
    // Texture for the robot
    sf::Texture m_robot_texture;
    // Orientation of the robot (texture will change according to it)
    Utils::Orientation m_robot_orientation;
};

#endif // GRID_H
