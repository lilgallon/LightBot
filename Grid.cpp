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
#include <exception>

namespace{
    const int POS_X_INDEX = 0;
    const int POS_Y_INDEX = 1;
    const int POS_ORIENTATION_INDEX = 1;
    const int HEIGHT_INDEX = 2;
    const int LIGHT_INDEX = 3;

    sf::Vector2f DEFAULT_GAP = {100,150};
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
Grid::Grid(std::vector<Cell*> cells, Robot *robot)
    :m_cells{cells}, m_robot{robot}, m_radius{65},m_error_drawing{false},m_over_cell{nullptr}, m_robot_orientation{Utils::Orientation::NONE},m_gap{DEFAULT_GAP}
{
    initLabel();
    initRobotRect();
}
Grid::Grid()
    :m_radius{65},m_error_drawing{false},m_over_cell{nullptr},m_robot_orientation{Utils::Orientation::NONE},m_gap{DEFAULT_GAP}
{
    initLabel();
    initRobotRect();
}

void Grid::initRobotRect(){
    m_robot_rect.setFillColor(sf::Color(255,255,255,255));
    m_robot_rect.setSize({100,100});
}

void Grid::initLabel(){
    std::string fontPath = "resources/fonts/";
    std::string fontName = "coolvetica.ttf";

    // Font load
    if (!m_font.loadFromFile(fontPath+fontName)) {
        //throw "Police "+POLICE+" manquante";
        std::cout << Utils::getTime() + "[Grid-ERROR]: Could not load the font" << std::endl;
        std::cout << Utils::getTime() + "[Grid-FIX]: Check \""
                     + fontPath+fontName + "\"" << std::endl;
        std::cout << Utils::getTime() + "[Grid-FIX]: The font will be ignored." << std::endl;
        m_text.setFont(m_font);
    }else{
        std::cout << Utils::getTime() + "[Grid-INFO]: Font loaded" << std::endl;
    }

    m_text.setFont(m_font);
    m_text.setColor(sf::Color::Black);
    m_text.setCharacterSize(20);

}

void Grid::initRobot(const std::string &line)
{
    std::vector<std::string> sub_string = Utils::split(line,";");


    m_robot->setPos({atoi(sub_string[POS_X_INDEX].c_str()),atoi(sub_string[POS_Y_INDEX].c_str())});

    int orientation = atof(sub_string[POS_ORIENTATION_INDEX].c_str());
    switch (orientation) {
    case 1:
            m_robot->setOrientation(Utils::Orientation::DOWN);
        break;
    case 2:
            m_robot->setOrientation(Utils::Orientation::DOWN_LEFT);
        break;
    case 3:
            m_robot->setOrientation(Utils::Orientation::DOWN_RIGHT);
        break;
    case 4:
            m_robot->setOrientation(Utils::Orientation::UP);
        break;
    case 5:
            m_robot->setOrientation(Utils::Orientation::UP_LEFT);
        break;
    case 6:
            m_robot->setOrientation(Utils::Orientation::UP_RIGHT);
        break;
    default:
        std::cout << Utils::getTime() + "[Grid-ERROR]: Orientation " + std::to_string(orientation) + " is invalid." << std::endl;
        m_robot->setOrientation(Utils::Orientation::DOWN);
        std::cout << Utils::getTime() + "[Grid-FIX]: The robot orientation has been set to DOWN" << std::endl;
        break;
    }

    //std::cout << "#### ROBOT POS : " + std::to_string(m_robot->getPos().x) + " ; " + std::to_string(m_robot->getPos().y) << std::endl;
    //std::cout << "#### ROBOT ORIENTATION : " + std::to_string(orientation) << std::endl;
}

void Grid::changeRobotTexture(Utils::Orientation orientation)
{
    std::string image;
    switch (orientation) {
    case Utils::Orientation::DOWN:
        image="down.png";
        break;
    case Utils::Orientation::DOWN_LEFT:
        image="down-left.png";
        break;
    case Utils::Orientation::DOWN_RIGHT:
        image="down-right.png";
        break;
    case Utils::Orientation::UP:
        image="up.png";
        break;
    case Utils::Orientation::UP_LEFT:
        image="up-left.png";
        break;
    case Utils::Orientation::UP_RIGHT:
        image="up-right.png";
        break;
    default:
        std::cout << Utils::getTime() + "[Grid-CRITICAL]: Invalid orientation ???" << std::endl;
        break;
    }

    if(!m_robot_texture.loadFromFile(Utils::IMG_PATH+image)){
        std::cout << Utils::getTime() + "[Grid-ERROR]: Orientation could not have been changed (texture)" << std::endl;
        std::cout << Utils::getTime() + "[Grid-FIX]: Check \""
                     + Utils::IMG_PATH + "\"" << std::endl;
        std::cout << Utils::getTime() + "[Grid-FIX]: The robot orientation texture will stay the same." << std::endl;
    }else{
        m_robot_rect.setTexture(&m_robot_texture);
    }
}
/*
void Grid::calculatePosition(Cell *c, sf::Vector2f &pos)
{
    if((int)c->getPos().x%2!=0 && (int)c->getPos().y%2==0){     // OK
        pos.x += c->getPos().x * (m_radius + m_radius* cos(Utils::PI/3.));
        if(c->getPos().y==0){
            pos.y -= (m_radius*sin(Utils::PI/3.));
        }else{
            pos.y += c->getPos().y * (m_radius*sin(Utils::PI/3.)) + (m_radius*sin(Utils::PI/3.));
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
}*/

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

void Grid::setRobot(Robot *robot)
{
    m_robot = robot;
}

/************************************************
*                   GETTERS                      *
*************************************************/
// TODO
// NOT CHECKED - It returns true if the mouse is on a cell
bool Grid::isOverCell(sf::Vector2i mouse){

    for(Cell* c : m_cells){
        c->setLight(false);
    }

    bool isOver = false;
    unsigned int i = 0;
    while(!isOver && i<m_cells.size()){

        sf::Vector2f pos = m_gap;

        Cell* c = m_cells.at(i);

        if((int)c->getPos().x%2!=0 && (int)c->getPos().y%2==0){     // OK
            pos.x += c->getPos().x * (m_radius + m_radius* cos(Utils::PI/3.));


            if(c->getPos().y==0){
                pos.y -= (m_radius*sin(Utils::PI/3.));
            }else{
                pos.y += c->getPos().y * (m_radius*sin(Utils::PI/3.)) + (m_radius*sin(Utils::PI/3.));
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


        isOver = Utils::abs(mouse.x-pos.x)<=m_radius
              && Utils::abs(mouse.y-pos.y)<=m_radius;
        i++;
    }
    i --;
    if(isOver){
        m_cells.at(i)->setLight(true);
        m_over_cell = m_cells.at(i);
    }else if(m_over_cell){
        m_over_cell = nullptr;
    }

    return isOver;
}

Cell *Grid::getOverCell() const
{
    return m_over_cell;
}
// Returns the grid
std::vector<Cell*> Grid::getGrid(){
    return m_cells;
}

/**************************************************
 *                 FILE STREAM
 * ************************************************/
void Grid::loadLevel(const std::string &level_id){

    std::fstream f;
    std::string line;
    std::string level_name;
    std::vector<std::string> sub_string;

    //std::vector<Cell*> cells;

    sf::Vector2f pos;
    int light;
    int height;


    // Tries to open the file
    f.open(Utils::LEVELS_PATH + level_id + ".txt", std::ios::in);
    if( f.fail() )
    {
        std::cout << Utils::getTime() + "[Level Loader-ERROR]: Could not load the level id #" + level_id
                  << std::endl;
    }else{

        if(!m_cells.empty()){
            for(Cell* c : m_cells){
                delete c;
                std::cout << Utils::getTime() + "[Level Loader-INFO]: Deleting a cell"
                          << std::endl;
            }
            std::cout << Utils::getTime() + "[Level Loader-INFO]: Clearing a cell"
                      << std::endl;
            m_cells.clear();

            std::cout << Utils::getTime() + "[Level Loader-INFO]: Deleting last level"
                      << std::endl;
        }


        // The first line corresponds to the level name
        std::cout << Utils::getTime() + "[Level Loader-INFO]: Reading the level"
                  << std::endl;
        f >> level_name;

        // ROBOT
        std::string robot_line;
        f >> robot_line;
        initRobot(robot_line);

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


            // Definition of the new cell, if this is not the end of the file
            // prevent an extra loop
            if(!f.eof()){
                Cell* c = new Cell(pos,height,light);
                m_cells.push_back(c);

            }


        }
        // Resizing because f.eof() make an extra loop
        //delete m_cells.at(m_cells.size()-1);
        //m_cells.resize(m_cells.size()-1);
        //m_cells.erase(m_cells.end()-1);
        // Erase the precedent grid to put the new one
        //this->setGrid(cells);
        std::cout << Utils::getTime() + "[Level Loader-INFO]: Level loaded"
                  << std::endl;
    }

    f.close();
}

void Grid::saveLevel(const std::string &level_id, const std::string &level_name){
    std::fstream f;
    std::string file = Utils::LEVELS_PATH + level_id + ".txt";

    std::fstream f_in;

    // Tries to open the file
    f_in.open(Utils::LEVELS_PATH + level_id + ".txt", std::ios::in);
    if( !f_in.fail() )
    {
        std::cout << Utils::getTime() + "[Level Saver-ERROR]: The level id#" + level_id + " already exists."
                  << std::endl;
        std::cout << Utils::getTime() + "[Level Saver-FIX]: The level id#" + level_id + " will not be saved."
                  << std::endl;
    }else{

        f.open(file.c_str(), std::ios::out);
        if( f.fail() )
        {
            std::cout << Utils::getTime() + "[Level Saver-ERROR]: Could not save the level id #" + level_id
                      << std::endl;
        }else{
            // Header
            f << level_name;
            f << "\n";
            f << m_robot->getPos().x << ";" << m_robot->getPos().y << ";" << (int)m_robot->getOrientation();
            for(Cell* c : m_cells){
                f << "\n";
                f << c->getPos().x << ";" << c->getPos().y << ";" << c->getHeight() << ";" << std::to_string(c->getLight());
            }
            std::cout << Utils::getTime() + "[Level Saver-INFO]: Level id #" + level_id + " has been saved."
                      << std::endl;
        }
    }
    f_in.close();
    f.close();

}

/************************************************
*                   OTHERS                    *
*************************************************/
// Draws the grid
void Grid::drawGrid(sf::RenderWindow& window, const sf::Vector2f &grid_pos){
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
        if(grid_pos.x!=-1 && grid_pos.y!=-1){
            m_gap = grid_pos;
        }else{
            m_gap = DEFAULT_GAP;
        }
        sf::Vector2f pos;
        sf::Color color_light(220,241,251,128);
        hexa.setPointCount(6);
        hexa.setFillColor(sf::Color::Transparent);
        hexa.setOutlineColor(sf::Color::Black);
        hexa.setOutlineThickness(2);
        hexa.setRotation(90);
        hexa.setRadius(m_radius);

        //sf::CircleShape robot_shape;
        //robot_shape.setFillColor(sf::Color::Red);
        // TODO : magic number m_radius/10 -> changer et mettre
        // en namespace ou qqch
        //robot_shape.setRadius(m_radius/10);



        for(Cell* c : m_cells){

            // HEXAGONES

            if(c->getLight()){
                hexa.setFillColor(color_light);
            }else{
                hexa.setFillColor(sf::Color::Transparent);
            }

            // If we don't want the grid at a specific position
            pos = m_gap;


            // Sets the center in the center :)
            hexa.setOrigin({c->getPos().x+m_radius,c->getPos().y+m_radius});
            m_robot_rect.setOrigin({(float)(m_robot->getPos().x+(double)m_radius/1.3),(float)(m_robot->getPos().y+(double)m_radius/1.3)});
            bool robot_is_there = false;


            if(c->getPos().x==m_robot->getPos().x && c->getPos().y == m_robot->getPos().y){
                robot_is_there = true;
            }

            if(m_robot->getOrientation()==Utils::Orientation::NONE || m_robot->getOrientation()!=m_robot_orientation){
                m_robot_orientation = m_robot->getOrientation();
                changeRobotTexture(m_robot_orientation);
            }



            if((int)c->getPos().x%2!=0 && (int)c->getPos().y%2==0){     // OK
                pos.x += c->getPos().x * (m_radius+1 + m_radius* cos(Utils::PI/3.)+1);
                if(c->getPos().y==0){
                    pos.y -= (m_radius*sin(Utils::PI/3.)+1);
                }else{
                    pos.y += c->getPos().y * (m_radius*sin(Utils::PI/3.)+1) + (m_radius*sin(Utils::PI/3.)+1);
                }
            }else if((int)c->getPos().x%2==0 && (int)c->getPos().y%2==0){
                pos.x += c->getPos().x * (m_radius+1+m_radius * cos(Utils::PI/3.)+1);
                if(c->getPos().y==0){
                    pos.y -= c->getPos().y * 2*(m_radius*sin(Utils::PI/3.)+1);
                }else{
                    pos.y += c->getPos().y * 2*(m_radius*sin(Utils::PI/3.)+1);
                }

            }else if((int)c->getPos().x%2!=0 && (int)c->getPos().y%2!=0){
                pos.x += c->getPos().x * (m_radius+1 + m_radius * cos(Utils::PI/3.)+1);
                if(c->getPos().y==1){
                    pos.y += c->getPos().y * (m_radius*sin(Utils::PI/3.)+1);
                }else{
                    pos.y += c->getPos().y * (m_radius*sin(Utils::PI/3.)+1) + 2*(m_radius*sin(Utils::PI/3.)+1);
                }
            }else if((int)c->getPos().x%2==0 && (int)c->getPos().y%2!=0){
                pos.x += c->getPos().x * (m_radius+1 + m_radius * cos(Utils::PI/3.)+1);
                pos.y += c->getPos().y * 2*(m_radius*sin(Utils::PI/3.)+1);
            }


            hexa.setPosition(pos);

            // TEXT w/ x;y
            //std::string label = std::to_string((int)c->getPos().x) + ";" + std::to_string((int)c->getPos().y);
            // TEXT w/ height
            std::string label = std::to_string(c->getHeight());

            m_text.setString(label);
            m_text.setPosition({pos.x-4,pos.y+m_radius/2});
            m_text.setColor(sf::Color(128,128,128,128));

            window.draw(hexa);
            window.draw(m_text);
            if(robot_is_there){
                m_robot_rect.setPosition(pos);
                window.draw(m_robot_rect);
            }
        }
    }


}
