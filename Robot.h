#ifndef ROBOT_H
#define ROBOT_H

#include <SFML/Graphics.hpp>
#include "Utils.h"

class Robot
{
private:
    sf::Vector2i m_pos;
    Utils::Orientation m_orientation;
    bool m_is_jumping;
public:
    Robot(sf::Vector2i pos, Utils::Orientation orientation);
    Robot() = default;

    sf::Vector2i getPos() const;
    Utils::Orientation getOrientation() const;
    bool isJumping() const;

    void setPos(const sf::Vector2i &pos);
    void setOrientation(const Utils::Orientation &orientation);
    void setJumping(const bool &b);
};

#endif // ROBOT_H
