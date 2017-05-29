#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>

class Cell
{

public:
    /** CONSTRUCTORS / DESCTRUCTORS **/
    Cell(const sf::Vector2f &pos, const int &height, const bool &light);
    Cell() = default;
    ~Cell() = default;

    /** SETTERS **/
    void setHeight(const int &height);
    void setLight(const bool &light);
    void setPos(const sf::Vector2f &pos);

    /** GETTERS**/
    int getHeight() const;
    bool getLight() const;
    sf::Vector2f getPos() const;

private:
    // Position (x,y) of the cell
    sf::Vector2f m_pos;
    // Height of the cell
    int m_height;
    // Light of the cell
    bool m_light;

};

#endif // CELL_H
