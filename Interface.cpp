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

#include "Interface.h"
#include "Utils.h"

namespace {
    const unsigned int SCREEN_WIDTH = 800;
    const unsigned int SCREEN_HEIGHT = 600;

    const std::string RES_PATH = "resources/";
    const std::string IMG_PATH = "images/";
}

/************************************************
*         CONSTRUCTORS / DESTRUCTORS            *
*************************************************/
// It initializes the buttons, the initial game state
Interface::Interface()
    :Application {SCREEN_WIDTH, SCREEN_HEIGHT, L"Lightbot"}, m_state {Utils::State::HOME}, m_first_loop{true}
{
    // IDEE
    // Une optimisation, si nécesasire, serait de ne charger que les boutons correspondant à
    // l'état du jeu dans lequel on est. Là, on charge tous les boutons du jeu entier en un coup
    // Bien evidemment, ce serait utile uniquement si il y a bp de lag en jeu mais ça devrait pas


    Theme *defaultTheme = new Theme(1);
    m_themes.push_back(defaultTheme);

    Button* home1 = new Button(Utils::State::LEVEL_SELECTION,{(float)SCREEN_WIDTH/2, SCREEN_HEIGHT/(float)1.8}     , {90, 70} , defaultTheme, "Play");
    //home1->setLabelText("Play");
    Button* home2 = new Button(Utils::State::CREDITS,{SCREEN_WIDTH/(float)1.11, SCREEN_HEIGHT/(float)1.05} , {150, 50}, defaultTheme, "Credits");
    //home2->setLabelText("Credits");
    m_buttons_home.push_back(home1);
    m_buttons_home.push_back(home2);

    Button* levelSelection1 = new Button(Utils::State::HOME,{(float)SCREEN_WIDTH/25, (float)SCREEN_HEIGHT/20}, {50, 50}, defaultTheme, "<-");
    //levelSelection1->setLabelText("<-");
    m_buttons_level_selection.push_back(levelSelection1);

    Button* credits1 = new Button(Utils::State::HOME,{(float)SCREEN_WIDTH/25, (float)SCREEN_HEIGHT/20}, {50, 50}, defaultTheme, "<-");
    //credits1->setLabelText("<-");
    m_buttons_credits.push_back(credits1);
}
// It deletes the pointers taht are contained in the buttons arrays and themes arrays
Interface::~Interface(){

    for(Button* b : m_buttons_home){
        delete b;
        std::cout << Utils::getTime() + "[EXIT-INFO]: Deleting a button" << std::endl;
    }
    for(Button* b : m_buttons_credits){
        delete b;
        std::cout << Utils::getTime() + "[EXIT-INFO]: Deleting a button" << std::endl;
    }
    for(Button* b : m_buttons_level_selection){
        delete b;
        std::cout << Utils::getTime() + "[EXIT-INFO]: Deleting a button" << std::endl;
    }
    for(Theme* t : m_themes){
        delete t;
        std::cout << Utils::getTime() + "[EXIT-INFO]: Deleting a theme" << std::endl;
    }
}

/************************************************
*               LOOP                            *
*************************************************/
// It draws things to the screen according to the game state
void Interface::loop()
{
    m_window.clear(sf::Color::White);
    draw_background();
    if(m_first_loop){
        loadBackground();
    }
    switch(m_state){
    case Utils::State::HOME:
        // TODO
        // Faire autre chose que le m_first_loop ?? --->  init()
        m_first_loop = false;
        // TODO
        // Fix pb avec les labels
        m_buttons_home[0]->setLabelText(m_buttons_home[0]->getLabelText());
        m_buttons_home[1]->setLabelText(m_buttons_home[1]->getLabelText());

        draw_buttons(m_buttons_home);
        break;
    case Utils::State::CREDITS:
        draw_buttons(m_buttons_credits);
        m_first_loop = false;
        break;
    case Utils::State::LEVEL_SELECTION:
        draw_buttons(m_buttons_level_selection);

        if(m_first_loop){
            // Création grid bob
            std::vector<Cell*> grid;
            Cell* c1 = new Cell({0,0},0,true);
            Cell* c2 = new Cell({1,0},0,true);
            Cell* c3 = new Cell({1,1},0,false);
            Cell* c4 = new Cell({0,1},0,false);
            grid.push_back(c1);
            grid.push_back(c2);
            grid.push_back(c3);
            grid.push_back(c4);
            m_grid = new Grid(grid);
        }

        m_grid->drawGrid(m_window);
        m_first_loop = false;
        break;
    case Utils::State::IN_GAME:
        m_first_loop = false;
        break;
    case Utils::State::LEVEL_EDITOR:
        m_first_loop = false;
        break;
    case Utils::State::END_GAME:
        m_first_loop = false;
        break;
    case Utils::State::IDLE:
        m_first_loop = false;
        break;
    default:
        break;
    }
    m_window.display();
}

/************************************************
*               PLAYER INTERACTIONS             *
*************************************************/
// Make things when the player clicks his mouse
void Interface::mouse_button_pressed(){
    switch (m_state) {
    case Utils::State::HOME:
        for(Button * b : m_buttons_home){
            changeState(isOnButton(b),b);
            changeButtonAppareance(false,b);
        }
        break;
    case Utils::State::CREDITS:
        for(Button * b : m_buttons_credits){
            changeState(isOnButton(b),b);
            changeButtonAppareance(false,b);
        }
        break;
    case Utils::State::LEVEL_SELECTION:
        for(Button * b : m_buttons_level_selection){
            changeState(isOnButton(b),b);
            changeButtonAppareance(false,b);
        }
        break;
    case Utils::State::IN_GAME:
        break;
    case Utils::State::LEVEL_EDITOR:
        break;
    case Utils::State::END_GAME:
        break;
    case Utils::State::IDLE:
        break;
    default:
        break;
    }
}
// Make things when the player releases his mouse
void Interface::mouse_button_released(){
    switch (m_state) {
    case Utils::State::HOME:
        break;
    case Utils::State::CREDITS:
        break;
    case Utils::State::LEVEL_SELECTION:
        break;
    case Utils::State::IN_GAME:
        break;
    case Utils::State::LEVEL_EDITOR:
        break;
    case Utils::State::END_GAME:
        break;
    case Utils::State::IDLE:
        break;
    default:
        break;
    }
}
// Make things when the player moves his mouse
void Interface::mouse_moved(){
    switch (m_state) {
    case Utils::State::HOME:
        for(Button * b : m_buttons_home){
            changeButtonAppareance(isOnButton(b),b);
        }
        break;
    case Utils::State::CREDITS:
        for(Button * b : m_buttons_credits){
            changeButtonAppareance(isOnButton(b),b);
        }
        break;
    case Utils::State::LEVEL_SELECTION:
        for(Button * b : m_buttons_level_selection){
            changeButtonAppareance(isOnButton(b),b);
        }
        break;
    case Utils::State::IN_GAME:
        break;
    case Utils::State::LEVEL_EDITOR:
        break;
    case Utils::State::END_GAME:
        break;
    case Utils::State::IDLE:
        break;
    default:
        break;
    }
}
// Make things when the player uses his keyboard
//void Interface::key_pressed (const sf::Event::KeyEvent & /*event*/);

/************************************************
*        DRAWING / UPDATE METHODS                *
*************************************************/
// It draws the buttons of the actual game state
void Interface::draw_buttons(std::vector<Button*> buttons){
    for(Button *b : buttons){
        b->draw_on(m_window);
    }
}
void Interface::draw_background(){
    m_window.draw(m_sprite);
}

// It changes a button appareace according to the mouse position
void Interface::changeButtonAppareance(const bool &onButton, Button* b){
    if(onButton){
        b->setColor(b->getTheme()->getRectOnRectFillColor());
        b->setOutlineColor(b->getTheme()->getRectOnRectOutlineColor());
        b->setLabelColor(b->getTheme()->getLabelOnRectFillColor());
    }else{
        b->setColor(b->getTheme()->getRectDefaultFillColor());
        b->setOutlineColor(b->getTheme()->getRectDefaultOutlineColor());
        b->setLabelColor(b->getTheme()->getLabelDefaultFillColor());
    }
}
// It changes the gamestate according to the button selected
void Interface::changeState(const bool &onButton, Button* b){
    if(onButton){
       std::cout << Utils::getTime() + "[Game State-INFO]: Changing the game state." << std::endl;
        m_first_loop = true;
        m_state = b->getState();
    }
}

/************************************************
*                UTILITY METHODS                *
*************************************************/
// Takes a button and calls the button's method to check
// if the mouse if over it
bool Interface::isOnButton(Button* b) const{
    return b->isOverRect(m_mouse);
}
// Takes a cell and calls the cell's method to check
// if the mouse if over it
bool Interface::isOnCell(Grid* g) const{
    return g->isOverCell(m_mouse);
}
// Load the background according to the game state
void Interface::loadBackground(){
    std::string image;
    switch (m_state) {
    case Utils::State::HOME:
        image = "lightbot-main.png";
        break;
    case Utils::State::CREDITS:
        image = "default.png";
        break;
    case Utils::State::LEVEL_SELECTION:
        image = "default.png";
        break;
    case Utils::State::IN_GAME:
        image = "default.png";
        break;
    case Utils::State::LEVEL_EDITOR:
        image = "default.png";
        break;
    case Utils::State::END_GAME:
        image = "default.png";
        break;
    case Utils::State::IDLE:
        image = "default.png";
        break;
    default:
        break;
    }
    if(!m_texture.loadFromFile(RES_PATH+IMG_PATH+image)){
        std::cout << Utils::getTime() + "[Texture-ERROR]: Could not load the background" << std::endl;
        std::cout << Utils::getTime() + "[Textur-FIX]: Check \""
                     + RES_PATH + IMG_PATH + "\"" << std::endl;
        std::cout << Utils::getTime() + "[Textur-FIX]: The texture will be ignored." << std::endl;
    }else{
        m_sprite.setTexture(m_texture);
        m_sprite.setPosition(0,0);
    }
}
