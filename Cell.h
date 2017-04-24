#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>

class Cell
{
private:
    int m_height;
    bool m_light;
    sf::Vector2f m_pos;

public:
    Cell(sf::Vector2i pos, int height, bool light);

    void setHeight(int height);
    void setLight(bool light);
    void setPos(sf::Vector2f pos);

    int getHeight();
    bool getLight();
    sf::Vector2f getPos();

};

#endif // CELL_H
