#include "Grid.h"
#include "Utils.h"
#include <iostream>
#include <math.h>

Grid::Grid(std::vector<Cell*> grid)
    :m_grid{grid}
{

}

Grid::~Grid(){
    for(Cell* c : m_grid){
        delete c;
    }
}

void Grid::drawGrid(sf::RenderWindow& window){
    // debug
    sf::CircleShape center;
    center.setFillColor(sf::Color::Red);
    center.setRadius(1);

    sf::CircleShape hexa;
    int radius = 50;
    sf::Vector2f gap = {150,150};
    sf::Vector2f pos;
    hexa.setPointCount(6);
    hexa.setFillColor(sf::Color::Transparent);
    hexa.setOutlineColor(sf::Color::Black);
    hexa.setOutlineThickness(2);
    hexa.setRadius(radius);
    hexa.setRotation(90);
    for(Cell* c : m_grid){

        //pos.x = gap.x + c->getPos().x * (radius) + radius * cos(Utils::PI/3));
        //pos.y = gap.y + c->getPos().y * (radius * sin(Utils::PI/3));

        pos = gap;

        // Sets the center in the center :)
        hexa.setOrigin({c->getPos().x+radius,c->getPos().y+radius});

        if((int)c->getPos().x%2!=0 && (int)c->getPos().y%2==0){     // OK
            pos.x += c->getPos().x * (radius + radius * cos(Utils::PI/3.));

            if(c->getPos().y==0){
                pos.y -= (radius*sin(Utils::PI/3.));
            }else{
                pos.y -= c->getPos().y * (radius*sin(Utils::PI/3.));
            }

        }else if((int)c->getPos().x%2==0 && (int)c->getPos().y%2==0){   //OK
            pos.x += c->getPos().x * (radius+radius * cos(Utils::PI/3.));
            pos.y -= c->getPos().y * 2*(radius*sin(Utils::PI/3.));
            /*
            if(c->getPos().y==0){
                pos.y -= (radius*sin(Utils::PI/3.));
            }else{
                pos.y -= c->getPos().y * (radius*sin(Utils::PI/3.));
            }*/

        }else if((int)c->getPos().x%2!=0 && (int)c->getPos().y%2!=0){       //OK
            pos.x += c->getPos().x * (radius + radius * cos(Utils::PI/3.));
            pos.y += c->getPos().y * (radius*sin(Utils::PI/3.));
        }else if((int)c->getPos().x%2==0 && (int)c->getPos().y%2!=0){
            pos.x += c->getPos().x * (radius + radius * cos(Utils::PI/3.));
            pos.y += c->getPos().y * 2*(radius*sin(Utils::PI/3.));
        }

        //std::cout << radius*sin(Utils::PI/3) << std::endl;




        center.setPosition(pos);

        //std::cout << "pos : " + std::to_string(pos.x) + ";" +  std::to_string(pos.y) << std::endl;
        hexa.setPosition(pos);
        window.draw(hexa);
        window.draw(center);
    }
}

void Grid::setGrid(std::vector<Cell*> grid){
    m_grid = grid;
}

std::vector<Cell*> Grid::getGrid(){
    return m_grid;
}
