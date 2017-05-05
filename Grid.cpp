//    This file is part of LightBot.
//
//    LightBot is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    LightBot is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with LightBot.  If not, see <http://www.gnu.org/licenses/>.

#include "Grid.h"
#include "Utils.h"
#include <iostream>
#include <math.h>

#include <fstream>
#include <cstdlib>

namespace{
    const std::string LEVELS_PATH = "levels/";
    const int POS_X_INDEX = 0;
    const int POS_Y_INDEX = 1;
    const int HEIGHT_INDEX = 2;
    const int LIGHT_INDEX = 3;
}

// TODO
// FAUT QQCH QUI CALCULE LE RADIUS EN FONCTION
// DE LA TAILLE DE LA GRILLE
// ARBITRAIREMENT, JE MET UN RADIUS DE 80!!
// m_radius = radius calculé
// ...

/************************************************
*         CONSTRUCTORS / DESTRUCTORS            *
*************************************************/
Grid::Grid(std::vector<Cell*> cells)
    :m_cells{cells},m_radius{80},m_error_drawing{false}
{

}
Grid::Grid()
    :m_radius{80},m_error_drawing{false}
{

}
Grid::~Grid(){
    for(Cell* c : m_cells){
        delete c;
    }
}

/************************************************
*                   SETTER                      *
*************************************************/
void Grid::setGrid(std::vector<Cell*> cells){
    m_cells = cells;
}

/************************************************
*                   GETTERS                      *
*************************************************/
// TODO
// NOT CHECKED - It returns true if the mouse is on a cell
bool Grid::isOverCell(sf::Vector2i mouse){
    bool isOver = false;
    unsigned int i = 0;
    while(!isOver && i<m_cells.size()){
        isOver = Utils::abs(mouse.x-m_cells.at(i)->getPos().x)<=m_radius
              && Utils::abs(mouse.y-m_cells.at(i)->getPos().y)<=m_radius;
        i++;
    }
    return isOver;
}
// Returns the grid
std::vector<Cell*> Grid::getGrid(){
    return m_cells;
}

/**************************************************
 *                 FILE STREAM
 * ************************************************/
void Grid::loadLevel(int level_id){

    std::fstream f;
    std::string line;
    std::string level_name;
    std::vector<std::string> sub_string;

    std::vector<Cell*> cells;

    sf::Vector2f pos;
    int light;
    int height;


    // Tries to open the file
    f.open(LEVELS_PATH + std::to_string(level_id) + ".txt", std::ios::in);
    if( f.fail() )
    {
        std::cout << Utils::getTime() + "[Level Loader-ERROR]: Could not load the level id #" + std::to_string(level_id)
                  << std::endl;
    }else{
        // Delete the precedent grid if there was one before
        /*
        for(Cell* c : m_cells){
            delete c;
        }*/


        // The first line corresponds to the level name
        std::cout << Utils::getTime() + "[Level Loader-INFO]: Reading the level"
                  << std::endl;
        f >> level_name;
        while( !f.eof() )
        {
            // Gets the line
            f >> line;
            sub_string = Utils::split(line,";");

            /* TODO CHECKER
            if(sub_string.size()==0){
                // say something
                // do something
            }
            if(sub_string.size()>4){
                // say something
                // do something
            }*/

            // Convert strings to good values
            pos.x = atof(sub_string[POS_X_INDEX].c_str());
            pos.y = atof(sub_string[POS_Y_INDEX].c_str());
            height = atoi(sub_string[HEIGHT_INDEX].c_str());
            light = (bool)atoi(sub_string[LIGHT_INDEX].c_str());

            /** CHECKER **
            // TODO
            if(pos.x>max){
                // say something
                // change pos_x
            }
            if(pos.y>max){
                // say something
                // change pos_y
            }
            if(height<0){
                // say something
                // change height
            }       ***/


            // Definition of the new cell
            Cell* c = new Cell(pos,height,light);
            cells.push_back(c);
        }
        // Erase the precedent grid to put the new one
        this->setGrid(cells);
        std::cout << Utils::getTime() + "[Level Loader-INFO]: Level loaded"
                  << std::endl;
    }

    f.close();




    /*
    try{

    }catch(Exception e){

    }
    */
    /*
    void remplirFichier( string fichier )
    {
        fstream f;

        f.open(fichier.c_str(), ios::out);
        if( f.fail() )
        {
            cerr << "ouverture en ecriture impossible" << endl;
         //   exit(EXIT_FAILURE);
        }
        for( int i=0 ; i<10 ; i++ )
            f << i << " ";
        f.close();
    }

    void ajoutFichier(string fichier){

        fstream f;
        f.open(fichier.c_str(), ios::out|ios::app);
        if( f.fail() )
        {
            cerr << "ouverture en ecriture impossible" << endl;
          //  exit(EXIT_FAILURE);
        }
        for( int i=10 ; i<20 ; i++ )
            f << i << " ";
        f.close();
    }
    */
}

/************************************************
*                   OTHERS                    *
*************************************************/
// Draws the grid
void Grid::drawGrid(sf::RenderWindow& window){
    // debug
    //sf::CircleShape center;
    //center.setFillColor(sf::Color::Red);
    //center.setRadius(1);

    if(m_cells.empty() && !m_error_drawing){
        std::cout << Utils::getTime() + "[Grid renderer-ERROR]: The grid seems to be empty"
                  << std::endl;
        std::cout << Utils::getTime() + "[Grid renderer-FIX]: The grid will not be displayed"
                  << std::endl;
        // m_error_drawing is used to display the error message only once instead of spamming it in the console
        m_error_drawing = true;
    }else if(!m_cells.empty()){
        m_error_drawing = false;
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
        for(Cell* c : m_cells){

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


}
