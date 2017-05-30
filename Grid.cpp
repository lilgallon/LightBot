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
//    Authors : Lilian Gallon, Tristan Renaudon

#include "Grid.h"
#include "Utils.h"
#include <iostream>
#include <math.h>

#include <fstream>
#include <cstdlib>

namespace{
    const int POS_X_INDEX = 0;
    const int POS_Y_INDEX = 1;
    const int POS_ORIENTATION_INDEX = 1;
    const int HEIGHT_INDEX = 2;
    const int LIGHT_INDEX = 3;

    const sf::Vector2f DEFAULT_GAP = {100,150};
    const sf::Vector2f DEFAULT_ROBOT_SIZE = {100,100};
    const int          DEFAULT_RADIUS = 65;

    const std::string  FONT_LEVELNAME       = "Ubuntu-L.ttf";
    const sf::Color    TEXT_LEVELNAME_COLOR = sf::Color::Black;
    const int          TEXT_LEVELNAME_SIZE  = 25;

    const std::string  FONT_LEVELHEIGHT       = "coolvetica.ttf";
    const sf::Color    TEXT_LEVELHEIGHT_COLOR = sf::Color(128,128,128,128);
    const int          TEXT_LEVELHEIGHT_SIZE  = 20;

    const sf::Color    CELL_LIGHT_COLOR = sf::Color(220,241,251,128);
    const sf::Color    CELL_NLIGHT_COLOR = sf::Color::Transparent;
    const sf::Color    CELL_FILL_COLOR = sf::Color::Transparent;
    const sf::Color    CELL_OUTLINE_COLOR = sf::Color::Black;
    const int          CELL_OUTLINE_THICKNESS = 2;

    const sf::Vector2f ROBOT_RECT_SIZE_JUMPING = {125,125};
    const sf::Vector2f ROBOT_RECT_SIZE_NJUMPING = {100,100};
}

/************************************************
*         CONSTRUCTORS / DESTRUCTORS            *
*************************************************/
Grid::Grid(std::vector<Cell*> cells, Robot *robot)
    :m_cells{cells}, m_robot{robot}, m_radius{DEFAULT_RADIUS}, m_gap{DEFAULT_GAP}, m_error_drawing{false},m_over_cell{nullptr}, m_robot_orientation{Utils::Orientation::NONE}
{
    initLabels();
    initRobotRect();
}
Grid::Grid()
    :m_radius{DEFAULT_RADIUS}, m_gap{DEFAULT_GAP}, m_error_drawing{false},m_over_cell{nullptr},m_robot_orientation{Utils::Orientation::NONE}
{
    initLabels();
    initRobotRect();
}

void Grid::initRobotRect(){
    m_robot_rect.setFillColor(sf::Color(255,255,255,255));
    m_robot_rect.setSize(DEFAULT_ROBOT_SIZE);
}

void Grid::initLabels(){

    // Font load (cell height)
    if (!m_font_levelheight.loadFromFile(Utils::FONT_PATH+FONT_LEVELHEIGHT)) {
        std::cout << Utils::getTime() + "[Grid-ERROR]: Could not load the font" << std::endl;
        std::cout << Utils::getTime() + "[Grid-FIX]: Check \""+ Utils::FONT_PATH+FONT_LEVELHEIGHT + "\"" << std::endl;
        std::cout << Utils::getTime() + "[Grid-FIX]: The font will be ignored." << std::endl;
    }else{
        m_text_levelheight.setFont(m_font_levelheight);
        std::cout << Utils::getTime() + "[Grid-INFO]: Font loaded" << std::endl;
    }

    m_text_levelheight.setColor(TEXT_LEVELHEIGHT_COLOR);
    m_text_levelheight.setCharacterSize(TEXT_LEVELHEIGHT_SIZE);

    // Font load (level name)
    if (!m_font_levelname.loadFromFile(Utils::FONT_PATH+FONT_LEVELNAME)) {
        std::cout << Utils::getTime() + "[Grid-ERROR]: Could not load the font" << std::endl;
        std::cout << Utils::getTime() + "[Grid-FIX]: Check \""+ Utils::FONT_PATH+FONT_LEVELNAME + "\"" << std::endl;
        std::cout << Utils::getTime() + "[Grid-FIX]: The font will be ignored." << std::endl;
    }else{
        m_text_levelname.setFont(m_font_levelname);
        std::cout << Utils::getTime() + "[Grid-INFO]: Font loaded" << std::endl;
    }

    m_text_levelname.setColor(TEXT_LEVELNAME_COLOR);
    m_text_levelname.setCharacterSize(TEXT_LEVELNAME_SIZE);

}

void Grid::initRobot(const std::string &line)
{
    // Divide the line with ';'
    std::vector<std::string> sub_string = Utils::split(line,";");

    bool error = false;
    if(sub_string.size()!=3){
        error = true;
        std::cout << Utils::getTime() + "[Level Loader-ERROR]: Robot line invalid: if the robot line seems to be valid, check if the level name has spaces (it should not)" << std::endl;
    }
    if(!error){
        // The robot receive its position
        m_robot->setPos({atoi(sub_string[POS_X_INDEX].c_str()),atoi(sub_string[POS_Y_INDEX].c_str())});

        // Get the orientation from the file and give it to the robot

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
    }
}

// Change the robot texture according to its orientation
void Grid::changeRobotTexture(const Utils::Orientation &orientation)
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
// It returns true if the mouse is on a cell
bool Grid::isOverCell(const sf::Vector2i &mouse){

    // Reset all the lights
    for(Cell* c : m_cells){
        c->setLight(false);
    }

    // We suppose that the mouse is not over a cell
    bool isOver = false;
    unsigned int i = 0;

    // We check if the mouse is over one of the cells of m_cells
    while(!isOver && i<m_cells.size()){
        // Gets the cell at the actual index
        Cell* c = m_cells.at(i);
        // Get the pos in pixels of the cell
        sf::Vector2f pos = Utils::positionToPixel(c->getPos(),m_gap,m_radius);
        // Compare mouse pos and hexagone pos (pixels)
        isOver = Utils::abs(mouse.x-pos.x)<=m_radius
                && Utils::abs(mouse.y-pos.y)<=m_radius;
        // The algorithm acts as if the hexagone was a circle
        i++;
    }
    i --;

    // If the mouse is over a cell, we change the light of this cell
    // And we get the cell which the mouse is over
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

std::vector<Cell*> Grid::getGrid(){
    return m_cells;
}

/**************************************************
 *                 FILE STREAM
 * ************************************************/
void Grid::loadLevel(const std::string &level_id){

    // Variables to read
    std::fstream f;
    std::string line;
    std::vector<std::string> sub_string;

    // Variable for the level
    std::string level_name;

    // Variables for the cell
    sf::Vector2f pos;
    int light;
    int height;


    // Tries to open the file
    f.open(Utils::LEVELS_PATH + level_id + ".txt", std::ios::in);
    if( f.fail() )
    {
        std::cout << Utils::getTime() + "[Level Loader-ERROR]: Could not load the level id #" + level_id << std::endl;
    }else{

        // If the grid already was loaded before, we reset it
        if(!m_cells.empty()){
            for(Cell* c : m_cells){
                delete c;
                std::cout << Utils::getTime() + "[Level Loader-INFO]: Deleting a cell" << std::endl;
            }
            m_cells.clear();
            std::cout << Utils::getTime() + "[Level Loader-INFO]: Deleting last level" << std::endl;
        }

        std::cout << Utils::getTime() + "[Level Loader-INFO]: Reading the level" << std::endl;

        // The first line corresponds to the level name
        f >> level_name;
        m_text_levelname.setString(level_name);

        // Robot values
        std::string robot_line;
        f >> robot_line;
        initRobot(robot_line);

        bool error_sub_string;
        bool error_values;

        while( !f.eof() )
        {
            error_sub_string = false;
            // Gets the line
            f >> line;
            sub_string = Utils::split(line,";");

            /* CHECKER */
            if(sub_string.size()==0){
                std::cout << Utils::getTime() + "[Level Loader-ERROR]: Error on the line, there is nothing" << std::endl;
                error_sub_string = true;
            }
            if(sub_string.size()>4){
                std::cout << Utils::getTime() + "[Level Loader-ERROR]: Error on the line, there is too much arguments" << std::endl;
                error_sub_string = true;
            }
            if(sub_string.size()<4){
                std::cout << Utils::getTime() + "[Level Loader-ERROR]: Error on the line, there not enough arguments" << std::endl;
                error_sub_string = true;
            }


            if(!error_sub_string){
                // Convert strings to good values
                pos.x = atof(sub_string[POS_X_INDEX].c_str());
                pos.y = atof(sub_string[POS_Y_INDEX].c_str());
                height = atoi(sub_string[HEIGHT_INDEX].c_str());
                light = (bool)atoi(sub_string[LIGHT_INDEX].c_str());


                /** CHECKER **/
                if(pos.x>7){
                    error_values = true;
                    std::cout << Utils::getTime() + "[Level Loader-ERROR]: pos X: " + std::to_string(pos.x) + " is invalid (>7)" << std::endl;
                }
                if(pos.y>4){
                    error_values = true;
                     std::cout << Utils::getTime() + "[Level Loader-ERROR]: pos Y: " + std::to_string(pos.y) + " is invalid (>4)" << std::endl;
                }
                if(height<0){
                     std::cout << Utils::getTime() + "[Level Loader-ERROR]: height: " + std::to_string(height) + " is invalid (<0)" << std::endl;
                    error_values = true;
                }
            }


            // Definition of the new cell, if this is not the end of the file
            // prevent an extra loop

            if(!f.eof() && !error_sub_string && !error_values){
                Cell* c = new Cell(pos,height,light);
                m_cells.push_back(c);
            }

        }
        std::cout << Utils::getTime() + "[Level Loader-INFO]: Level loaded" << std::endl;
    }

    f.close();
}

void Grid::saveLevel(const std::string &level_id, const std::string &level_name){

    // File stream
    std::fstream f;
    std::fstream f_in;

    // File adress (level)
    std::string file = Utils::LEVELS_PATH + level_id + ".txt";

    // Tries to open the file
    f_in.open(Utils::LEVELS_PATH + level_id + ".txt", std::ios::in);
    if( !f_in.fail() )
    {
        std::cout << Utils::getTime() + "[Level Saver-ERROR]: The level id#" + level_id + " already exists." << std::endl;
        std::cout << Utils::getTime() + "[Level Saver-FIX]: The level id#" + level_id + " will not be saved." << std::endl;
    }else{

        f.open(file.c_str(), std::ios::out);
        if( f.fail() )
        {
            std::cout << Utils::getTime() + "[Level Saver-ERROR]: Could not save the level id #" + level_id << std::endl;
        }else{
            // Level info
            f << level_name;
            f << "\n";
            // Robot infos
            f << m_robot->getPos().x << ";" << m_robot->getPos().y << ";" << (int)m_robot->getOrientation();
            // Cells infos
            for(Cell* c : m_cells){
                f << "\n";
                f << c->getPos().x << ";" << c->getPos().y << ";" << c->getHeight() << ";" << std::to_string(c->getLight());
            }
            std::cout << Utils::getTime() + "[Level Saver-INFO]: Level id #" + level_id + " has been saved." << std::endl;
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

    if(m_cells.empty() && !m_error_drawing){
        // If cells container is empty, we do not write the level
        std::cout << Utils::getTime() + "[Grid renderer-ERROR]: The grid seems to be empty" << std::endl;
        std::cout << Utils::getTime() + "[Grid renderer-FIX]: The grid will not be displayed" << std::endl;
        // m_error_drawing is used to display the error message only once instead of spamming it in the console
        m_error_drawing = true;
    }else if(!m_cells.empty()){
        m_error_drawing = false;

        // Sets the gap (-1;-1) indicates that we want the default one
        if(grid_pos.x!=-1 && grid_pos.y!=-1){
            m_gap = grid_pos;
        }else{
            m_gap = DEFAULT_GAP;
        }

        sf::CircleShape hexa;
        hexa.setPointCount(6);
        hexa.setRotation(90);
        hexa.setRadius(m_radius);
        hexa.setFillColor(CELL_FILL_COLOR);
        hexa.setOutlineColor(CELL_OUTLINE_COLOR);
        hexa.setOutlineThickness(CELL_OUTLINE_THICKNESS);

        for(Cell* c : m_cells){

            // If the cell has the light on, the color is different
            if(c->getLight()){
                hexa.setFillColor(CELL_LIGHT_COLOR);
            }else{
                hexa.setFillColor(CELL_NLIGHT_COLOR);
            }

            // Sets the origins in the center
            hexa.setOrigin({c->getPos().x+m_radius,c->getPos().y+m_radius});
            m_robot_rect.setOrigin({(float)(m_robot->getPos().x+(double)m_radius/1.3),(float)(m_robot->getPos().y+(double)m_radius/1.3)});

            // We suppose that the robot is not here, we will draw it after if he is on the current cell
            bool robot_is_there = false;
            if(c->getPos().x==m_robot->getPos().x && c->getPos().y == m_robot->getPos().y){
                robot_is_there = true;
            }

            // If the orientation of the robot has changed, we change the texture
            if(m_robot->getOrientation()==Utils::Orientation::NONE || m_robot->getOrientation()!=m_robot_orientation){
                m_robot_orientation = m_robot->getOrientation();
                changeRobotTexture(m_robot_orientation);
            }

            // Convert the position of the cell from index to pixels
            sf::Vector2f pos = Utils::positionToPixel(c->getPos(),m_gap,m_radius);

            // Sets the cell at this position
            hexa.setPosition(pos);

            // TEXT with x;y
            //std::string label = std::to_string((int)c->getPos().x) + ";" + std::to_string((int)c->getPos().y);
            // TEXT with height
            std::string label = std::to_string(c->getHeight());

            // The text where is the height
            m_text_levelheight.setString(label);
            m_text_levelheight.setColor(sf::Color(TEXT_LEVELHEIGHT_COLOR));
            // -4 here is to adjust the text position since m_text.getGlobalBounds().height is not working well
            // m_radius/2 is to show the text at the middle of the cell (the origin is on the top left corner)
            m_text_levelheight.setPosition({pos.x-4,pos.y+m_radius/2});

            m_text_levelname.setColor(sf::Color(TEXT_LEVELNAME_COLOR));
            // -4 here is to adjust the text position since m_text.getGlobalBounds().height is not working well
            // m_radius/2 is to show the text at the middle of the cell (the origin is on the top left corner)
            m_text_levelname.setPosition({0,0});
            // Draw elements
            window.draw(hexa);
            window.draw(m_text_levelheight);
            window.draw(m_text_levelname);

            // If the robot is on the current cell, we draw it according to if its jumping or not
            if(robot_is_there){
                if(m_robot->isJumping()){
                    m_robot_rect.setSize(ROBOT_RECT_SIZE_JUMPING);
                    m_robot_rect.setOrigin({ROBOT_RECT_SIZE_JUMPING.x/2,ROBOT_RECT_SIZE_JUMPING.y/2});
                }else{
                    m_robot_rect.setSize(ROBOT_RECT_SIZE_NJUMPING);
                    m_robot_rect.setOrigin({ROBOT_RECT_SIZE_NJUMPING.x/2,ROBOT_RECT_SIZE_NJUMPING.y/2});
                }
                m_robot_rect.setPosition(pos);
                window.draw(m_robot_rect);
            }
        }
    }
}
