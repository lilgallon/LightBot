#include "Grid.h"
#include "Utils.h"
#include <iostream>
#include <math.h>

Grid::Grid(std::vector<Cell*> grid)
    :m_grid{grid},m_radius{80}
{

}

Grid::~Grid(){
    for(Cell* c : m_grid){
        delete c;
    }
}

void Grid::drawGrid(sf::RenderWindow& window){
    // debug
    //sf::CircleShape center;
    //center.setFillColor(sf::Color::Red);
    //center.setRadius(1);

    // FAUT QQCH QUI CALCULE LE RADIUS EN FONCTION
    // DE LA TAILLE DE LA GRILLE
    // ARBITRAIREMENT, JE MET UN RADIUS DE 80!!
    // m_radius = radius calculé
    // ...

    sf::CircleShape hexa;
    sf::Vector2f gap = {150,150};
    sf::Vector2f pos;
    sf::Color color_light(128,128,128,128);
    hexa.setPointCount(6);
    hexa.setFillColor(sf::Color::Transparent);
    hexa.setOutlineColor(sf::Color::Black);
    hexa.setOutlineThickness(2);
    hexa.setRotation(90);
    hexa.setRadius(m_radius);
    for(Cell* c : m_grid){

        if(c->getLight()){
            hexa.setFillColor(color_light);
        }else{
            hexa.setFillColor(sf::Color::Transparent);
        }

        pos = gap;

        // Sets the center in the center :)
        hexa.setOrigin({c->getPos().x+m_radius,c->getPos().y+m_radius});

        if((int)c->getPos().x%2!=0 && (int)c->getPos().y%2==0){     // OK
            pos.x += c->getPos().x * (m_radius + m_radius* cos(Utils::PI/3.));

            if(c->getPos().y==0){
                pos.y -= (m_radius*sin(Utils::PI/3.));
            }else{
                pos.y -= c->getPos().y * (m_radius*sin(Utils::PI/3.));
            }
        }else if((int)c->getPos().x%2==0 && (int)c->getPos().y%2==0){
            pos.x += c->getPos().x * (m_radius+m_radius * cos(Utils::PI/3.));
            pos.y -= c->getPos().y * 2*(m_radius*sin(Utils::PI/3.));
        }else if((int)c->getPos().x%2!=0 && (int)c->getPos().y%2!=0){
            pos.x += c->getPos().x * (m_radius + m_radius * cos(Utils::PI/3.));
            pos.y += c->getPos().y * (m_radius*sin(Utils::PI/3.));
        }else if((int)c->getPos().x%2==0 && (int)c->getPos().y%2!=0){
            pos.x += c->getPos().x * (m_radius + m_radius * cos(Utils::PI/3.));
            pos.y += c->getPos().y * 2*(m_radius*sin(Utils::PI/3.));
        }
        //center.setPosition(pos);
        hexa.setPosition(pos);
        window.draw(hexa);
        //window.draw(center);
    }
}

bool Grid::isOverCell(sf::Vector2i mouse){
    bool isOver = false;
    int i = 0;
    while(!isOver && i<m_grid.size()){
        isOver = Utils::abs(mouse.x-m_grid.at(i)->getPos().x)<=m_radius
              && Utils::abs(mouse.y-m_grid.at(i)->getPos().y)<=m_radius;
        i++;
    }
    return isOver;
}

void Grid::setGrid(std::vector<Cell*> grid){
    m_grid = grid;
}

std::vector<Cell*> Grid::getGrid(){
    return m_grid;
}
