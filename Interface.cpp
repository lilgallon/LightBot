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

    const sf::Vector2f ACTION_BUTTON_SIZE = {30,30};
}

/************************************************
*         CONSTRUCTORS / DESTRUCTORS            *
*************************************************/
// It initializes the buttons, the initial game state
Interface::Interface()
    :Application {SCREEN_WIDTH, SCREEN_HEIGHT, L"Lightbot"}, m_state {Utils::State::HOME}, m_first_loop{true}, m_selected_level{-1}, m_selected_button{nullptr},m_grid{new Grid()}
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


    // TODO --> add a parameter with the texture
    Button* in_game1 = new Button(Utils::Action::FORWARD,{20+(ACTION_BUTTON_SIZE.x+10)*0,SCREEN_HEIGHT-20},ACTION_BUTTON_SIZE,defaultTheme,"F");
    Button* in_game2 = new Button(Utils::Action::JUMP,{20+(ACTION_BUTTON_SIZE.x+10)*1,SCREEN_HEIGHT-20},ACTION_BUTTON_SIZE,defaultTheme,"J");
    Button* in_game3 = new Button(Utils::Action::LIGHT,{20+(ACTION_BUTTON_SIZE.x+10)*2,SCREEN_HEIGHT-20},ACTION_BUTTON_SIZE,defaultTheme,"L");
    Button* in_game4 = new Button(Utils::Action::PROG_P1,{20+(ACTION_BUTTON_SIZE.x+10)*3,SCREEN_HEIGHT-20},ACTION_BUTTON_SIZE,defaultTheme,"P1");
    Button* in_game5 = new Button(Utils::Action::PROG_P2,{20+(ACTION_BUTTON_SIZE.x+10)*4,SCREEN_HEIGHT-20},ACTION_BUTTON_SIZE,defaultTheme,"P2");
    Button* in_game6 = new Button(Utils::Action::TURN_CLOCKWISE,{20+(ACTION_BUTTON_SIZE.x+10)*5,SCREEN_HEIGHT-20},ACTION_BUTTON_SIZE,defaultTheme,"TCW");
    Button* in_game7 = new Button(Utils::Action::TURN_COUNTERCLOCK,{20+(ACTION_BUTTON_SIZE.x+10)*6,SCREEN_HEIGHT-20},ACTION_BUTTON_SIZE,defaultTheme,"TCC");

    m_buttons_in_game.push_back(in_game1);
    m_buttons_in_game.push_back(in_game2);
    m_buttons_in_game.push_back(in_game3);
    m_buttons_in_game.push_back(in_game4);
    m_buttons_in_game.push_back(in_game5);
    m_buttons_in_game.push_back(in_game6);
    m_buttons_in_game.push_back(in_game7);

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
    for(Button* b : m_buttons_in_game){
        delete b;
        std::cout << Utils::getTime() + "[EXIT-INFO]: Deleting a button" << std::endl;
    }
    for(Theme* t : m_themes){
        delete t;
        std::cout << Utils::getTime() + "[EXIT-INFO]: Deleting a theme" << std::endl;
    }
    delete m_grid;
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

        draw_buttons(m_buttons_home);
        break;
    case Utils::State::CREDITS:
        draw_buttons(m_buttons_credits);
        break;
    case Utils::State::LEVEL_SELECTION:
        draw_buttons(m_buttons_level_selection);

        if(m_first_loop){
            // TODO
            // init plutot non?
            // loadLevel doesn't cause a crash when loading a inexistant level
            m_grid->loadLevel("1");
            m_grid->saveLevel("99","testage");
        }

        m_grid->drawGrid(m_window);
        break;
    case Utils::State::IN_GAME:
        draw_buttons(m_buttons_in_game);

        if(m_first_loop){
            // Load the selected level
            m_grid->loadLevel(m_selected_level);
            //m_grid->saveLevel("test","debug");
        }
        m_grid->drawGrid(m_window);

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

    m_first_loop = false;

}

/************************************************
*               PLAYER INTERACTIONS             *
*************************************************/
// Make things when the player clicks his mouse
void Interface::mouse_button_pressed(){

    switch (m_state) {
    case Utils::State::HOME:
        for(Button * b : m_buttons_home){
            buttonChangeState(isOnButton(b),b);
            changeButtonAppareance(false,b);
        }
        break;
    case Utils::State::CREDITS:
        for(Button * b : m_buttons_credits){
            buttonChangeState(isOnButton(b),b);
            changeButtonAppareance(false,b);
        }
        break;
    case Utils::State::LEVEL_SELECTION:
        for(Button * b : m_buttons_level_selection){
            buttonChangeState(isOnButton(b),b);
            changeButtonAppareance(false,b);
        }
        if(m_grid->isOverCell(m_mouse)){

            changeSelectedCell();
            changeGameState(Utils::State::IN_GAME);
        }
        break;
    case Utils::State::IN_GAME:
        for(Button * b : m_buttons_in_game){
            changeButtonAppareance(false,b);
        }
        // Get the selected button to move it later
        m_selected_button = getSelectedButton();
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
    m_selected_button = nullptr;
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
        // Changes the level grid according to the mouse (level selection)
        m_grid->isOverCell(m_mouse);
        break;
    case Utils::State::IN_GAME:
        for(Button * b : m_buttons_in_game){
            changeButtonAppareance(isOnButton(b),b);
        }
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

void Interface::mouse_pressing()
{
    switch (m_state) {
    case Utils::State::HOME:
        break;
    case Utils::State::CREDITS:
        break;
    case Utils::State::LEVEL_SELECTION:
        break;
    case Utils::State::IN_GAME:
        if(m_selected_button!=nullptr){
            draw_button_at(*m_selected_button,m_mouse);
        }
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
        // TODO
        // Fix pb avec les labels
        b->setLabelText(b->getLabelText());
        b->draw_on(m_window);
    }
}

void Interface::draw_button_at(const Button &button, sf::Vector2i pos)
{
    // TODO
    // FINIR
    Button b = Button(button);
    b.setPosition({(float)pos.x,(float)pos.y});
    //std::cout << b.getButton().getFillColor().r << "," << b.getButton().getFillColor().g << "," << b.getButton().getFillColor().b << std::endl;
    //std::cout << std::to_string(b.getButton().getSize().x) << std::endl;
    std::cout << std::to_string(b.getButton().getPosition().x) << std::endl;
    b.draw_on(m_window);

    //m_window.draw(b.getButton());
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
void Interface::buttonChangeState(const bool &onButton, Button* b){
    if(onButton){
        changeGameState(b->getState());
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

void Interface::changeSelectedCell()
{
    // If the mouse is over a cell and the user clicked on it
    // then he has selected the level
    // now we have to get the level that he choose
    // REMINDER: the level id is built on this template : "xy"
    std::string s;
    s = std::to_string((int)m_grid->getOverCell()->getPos().x)
            + std::to_string((int)m_grid->getOverCell()->getPos().y);
    m_selected_level = s;//atoi(s.c_str());
    std::cout << Utils::getTime() + "[Game-INFO]: Level id #" + s + " selected" << std::endl;
}

void Interface::changeGameState(const Utils::State &s)
{
    std::cout << Utils::getTime() + "[Game State-INFO]: Changing the game state." << std::endl;
    m_state = s;
    m_first_loop = true;
}

Button* Interface::getSelectedButton()
{
    unsigned int i = 0;

    while(i<m_buttons_in_game.size() && m_selected_button==nullptr){
        if(isOnButton(m_buttons_in_game.at(i))){
            m_selected_button = m_buttons_in_game.at(i);
            std::cout << Utils::getTime() + "[Game State-INFO]: Button selected." << std::endl;
        }
        i ++;
    }

    return m_selected_button;
}
