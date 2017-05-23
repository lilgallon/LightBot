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
    const unsigned int SCREEN_WIDTH = 1280;
    const unsigned int SCREEN_HEIGHT = 720;

    const sf::Vector2f ACTION_BUTTON_SIZE = {80,80};

    const sf::Vector2f PROGRAM_BOX_SIZE_MAIN = {360,218};
    const sf::Vector2f PROGRAM_BOX_POS_MAIN = {SCREEN_WIDTH-PROGRAM_BOX_SIZE_MAIN.x-20,35};

    const sf::Vector2f PROGRAM_BOX_SIZE_P = {PROGRAM_BOX_SIZE_MAIN.x,145};

    const sf::Vector2f PROGRAM_BOX_POS_P1 = {SCREEN_WIDTH-PROGRAM_BOX_SIZE_MAIN.x-20,35+PROGRAM_BOX_SIZE_MAIN.y+40};
    const sf::Vector2f PROGRAM_BOX_POS_P2 = {PROGRAM_BOX_POS_P1.x,PROGRAM_BOX_POS_P1.y+PROGRAM_BOX_SIZE_P.y+40};

    const int RUN = 1;
    const int CLEAR = 2;
    const int RETRY = 3;
    const int BACK = 4;
}

/************************************************
*         CONSTRUCTORS / DESTRUCTORS            *
*************************************************/
// It initializes the buttons, the initial game state
Interface::Interface()
    :Application {SCREEN_WIDTH, SCREEN_HEIGHT, L"Lightbot"}, m_state {Utils::State::HOME}, m_first_loop{true}, m_program_end_screen{false}, m_selected_level{-1}, m_selected_button{nullptr},m_grid{new Grid()},m_robot{new Robot()}
{
    // IDEE
    // Une optimisation, si nécesasire, serait de ne charger que les boutons correspondant à
    // l'état du jeu dans lequel on est. Là, on charge tous les boutons du jeu entier en un coup
    // Bien evidemment, ce serait utile uniquement si il y a bp de lag en jeu mais ça devrait pas


    Theme *defaultTheme = new Theme(1);
    m_themes.push_back(defaultTheme);
    Theme *actionTheme = new Theme(2);
    m_themes.push_back(actionTheme);

    Button* play = new Button(Utils::State::LEVEL_SELECTION,{(float)SCREEN_WIDTH/2.-90/2, (float)SCREEN_HEIGHT/2-50/2}     , {90, 50} , defaultTheme, "Play");
    //home1->setLabelText("Play");
    Button* credits = new Button(Utils::State::CREDITS,{(float)SCREEN_WIDTH/2.-90/2, (float)SCREEN_HEIGHT/2+50/2+10} , {90, 50}, defaultTheme, "Credits");
    //home2->setLabelText("Credits");
    m_buttons_home.push_back(play);
    m_buttons_home.push_back(credits);

    Button* back_to_menu = new Button(Utils::State::HOME,{(float)SCREEN_WIDTH/2-80/2-20, (float)SCREEN_HEIGHT-50-20}, {80, 50}, defaultTheme, "Back");
    Button* go_to_editor = new Button(Utils::State::LEVEL_EDITOR, {(float)SCREEN_WIDTH/2+80/2+20, (float)SCREEN_HEIGHT-50-20} , {80, 50}, defaultTheme, "Editor");
    //levelSelection1->setLabelText("<-");
    m_buttons_level_selection.push_back(back_to_menu);
    m_buttons_level_selection.push_back(go_to_editor);

    Button* credits1 = new Button(Utils::State::HOME,{(float)SCREEN_WIDTH/25, (float)SCREEN_HEIGHT/20}, {50, 50}, defaultTheme, "<-");
    //credits1->setLabelText("<-");
    m_buttons_credits.push_back(credits1);

    /*
    // TODO --> add a parameter with the texture
    Button* in_game1 = new Button(Utils::Action::FORWARD,{ACTION_BUTTON_SIZE.x+(ACTION_BUTTON_SIZE.x+10)*0,SCREEN_HEIGHT-ACTION_BUTTON_SIZE.y/2-20},ACTION_BUTTON_SIZE,defaultTheme,"F");
    Button* in_game2 = new Button(Utils::Action::JUMP,{ACTION_BUTTON_SIZE.x+(ACTION_BUTTON_SIZE.x+10)*1,SCREEN_HEIGHT-ACTION_BUTTON_SIZE.y/2-20},ACTION_BUTTON_SIZE,defaultTheme,"J");
    Button* in_game3 = new Button(Utils::Action::LIGHT,{ACTION_BUTTON_SIZE.x+(ACTION_BUTTON_SIZE.x+10)*2,SCREEN_HEIGHT-ACTION_BUTTON_SIZE.y/2-20},ACTION_BUTTON_SIZE,defaultTheme,"L");
    Button* in_game4 = new Button(Utils::Action::PROG_P1,{ACTION_BUTTON_SIZE.x+(ACTION_BUTTON_SIZE.x+10)*3,SCREEN_HEIGHT-ACTION_BUTTON_SIZE.y/2-20},ACTION_BUTTON_SIZE,defaultTheme,"P1");
    Button* in_game5 = new Button(Utils::Action::PROG_P2,{ACTION_BUTTON_SIZE.x+(ACTION_BUTTON_SIZE.x+10)*4,SCREEN_HEIGHT-ACTION_BUTTON_SIZE.y/2-20},ACTION_BUTTON_SIZE,defaultTheme,"P2");
    Button* in_game6 = new Button(Utils::Action::TURN_CLOCKWISE,{ACTION_BUTTON_SIZE.x+(ACTION_BUTTON_SIZE.x+10)*5,SCREEN_HEIGHT-ACTION_BUTTON_SIZE.y/2-20},ACTION_BUTTON_SIZE,defaultTheme,"TCW");
    Button* in_game7 = new Button(Utils::Action::TURN_COUNTERCLOCK,{ACTION_BUTTON_SIZE.x+(ACTION_BUTTON_SIZE.x+10)*6,SCREEN_HEIGHT-ACTION_BUTTON_SIZE.y/2-20},ACTION_BUTTON_SIZE,defaultTheme,"TCC");
    */

    Button* in_game1 = new Button(Utils::Action::FORWARD,{40+ACTION_BUTTON_SIZE.x+(ACTION_BUTTON_SIZE.x+10)*0,SCREEN_HEIGHT-ACTION_BUTTON_SIZE.y/2-20},ACTION_BUTTON_SIZE,actionTheme);
    Button* in_game2 = new Button(Utils::Action::JUMP,{40+ACTION_BUTTON_SIZE.x+(ACTION_BUTTON_SIZE.x+10)*1,SCREEN_HEIGHT-ACTION_BUTTON_SIZE.y/2-20},ACTION_BUTTON_SIZE,actionTheme);
    Button* in_game3 = new Button(Utils::Action::LIGHT,{40+ACTION_BUTTON_SIZE.x+(ACTION_BUTTON_SIZE.x+10)*2,SCREEN_HEIGHT-ACTION_BUTTON_SIZE.y/2-20},ACTION_BUTTON_SIZE,actionTheme);
    Button* in_game4 = new Button(Utils::Action::PROG_P1,{40+ACTION_BUTTON_SIZE.x+(ACTION_BUTTON_SIZE.x+10)*3,SCREEN_HEIGHT-ACTION_BUTTON_SIZE.y/2-20},ACTION_BUTTON_SIZE,actionTheme);
    Button* in_game5 = new Button(Utils::Action::PROG_P2,{40+ACTION_BUTTON_SIZE.x+(ACTION_BUTTON_SIZE.x+10)*4,SCREEN_HEIGHT-ACTION_BUTTON_SIZE.y/2-20},ACTION_BUTTON_SIZE,actionTheme);
    Button* in_game6 = new Button(Utils::Action::TURN_CLOCKWISE,{40+ACTION_BUTTON_SIZE.x+(ACTION_BUTTON_SIZE.x+10)*5,SCREEN_HEIGHT-ACTION_BUTTON_SIZE.y/2-20},ACTION_BUTTON_SIZE,actionTheme);
    Button* in_game7 = new Button(Utils::Action::TURN_COUNTERCLOCK,{40+ACTION_BUTTON_SIZE.x+(ACTION_BUTTON_SIZE.x+10)*6,SCREEN_HEIGHT-ACTION_BUTTON_SIZE.y/2-20},ACTION_BUTTON_SIZE,actionTheme);

    Button* run_prgm = new Button(RUN,{SCREEN_WIDTH/(float)1.11, SCREEN_HEIGHT/(float)1.05} , {150, 50}, defaultTheme, "RUN");
    Button* clear_prgms = new Button(CLEAR,{SCREEN_WIDTH/(float)1.3, SCREEN_HEIGHT/(float)1.05} , {150, 50}, defaultTheme, "CLEAR");

    m_buttons_in_game.push_back(in_game1);
    m_buttons_in_game.push_back(in_game2);
    m_buttons_in_game.push_back(in_game3);
    m_buttons_in_game.push_back(in_game4);
    m_buttons_in_game.push_back(in_game5);
    m_buttons_in_game.push_back(in_game6);
    m_buttons_in_game.push_back(in_game7);

    m_buttons_in_game.push_back(run_prgm);
    m_buttons_in_game.push_back(clear_prgms);


    ProgramBox* prgm_main = new ProgramBox(PROGRAM_BOX_POS_MAIN,PROGRAM_BOX_SIZE_MAIN,sf::Color(128,128,128,128),sf::Color::Black,2,"Main",Utils::TypeProg::MAIN);
    ProgramBox* prgm_p1 = new ProgramBox(PROGRAM_BOX_POS_P1,PROGRAM_BOX_SIZE_P,sf::Color(128,128,128,128),sf::Color::Black,2,"P1",Utils::TypeProg::P1);
    ProgramBox* prgm_p2 = new ProgramBox(PROGRAM_BOX_POS_P2,PROGRAM_BOX_SIZE_P,sf::Color(128,128,128,128),sf::Color::Black,2,"P2",Utils::TypeProg::P2);

    m_program_boxes.push_back(prgm_main);
    m_program_boxes.push_back(prgm_p1);
    m_program_boxes.push_back(prgm_p2);

    Button* retry = new Button(RETRY,{SCREEN_HEIGHT/2,SCREEN_WIDTH/2},{100,100},defaultTheme,"RETRY");
    Button* back = new Button(BACK,{SCREEN_HEIGHT/2+80,SCREEN_WIDTH/2},{150,100},defaultTheme,"BACK TO MENU");


    m_buttons_end_program.push_back(retry);
    m_buttons_end_program.push_back(back);
    // The grid needs a robot before puttin a grid on it
    // because loading a level (a grid) will use the robot
    // instance
    m_grid->setRobot(m_robot);

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
    for(Button* b : m_buttons_end_program){
        delete b;
        std::cout << Utils::getTime() + "[EXIT-INFO]: Deleting a button" << std::endl;
    }
    for(Theme* t : m_themes){
        delete t;
        std::cout << Utils::getTime() + "[EXIT-INFO]: Deleting a theme" << std::endl;
    }
    for(ProgramBox* p : m_program_boxes){
        delete p;
    }
    delete m_grid;
    delete m_robot;
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
            //m_grid->saveLevel("99","testage");
        }

        m_grid->drawGrid(m_window, {250,350});
        break;
    case Utils::State::IN_GAME:
        draw_buttons(m_buttons_in_game);

        if(m_first_loop){
            // Load the selected level
            m_grid->loadLevel(m_selected_level);
            //m_grid->saveLevel("test","debug");
        }

        m_grid->drawGrid(m_window, {-1,-1});
        draw_prgm_boxes(m_program_boxes);

        m_program_end_screen=true;
        // After the execution of the program
        if(m_program_end_screen){
            // Grey transparent background over the game
            sf::RectangleShape rect;
            rect.setSize({SCREEN_WIDTH,SCREEN_HEIGHT});
            rect.setFillColor(sf::Color(128,128,128,150));
            rect.setPosition(0,0);
            m_window.draw(rect);

            draw_buttons(m_buttons_end_program);

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
            // If the mouse is on the run program button
            if(b->isOverRect(m_mouse)){
                if(b->getUtility()==RUN){
                    ProgramHandler* prog = new ProgramHandler(m_program_boxes[0],m_program_boxes[1],m_program_boxes[2],m_robot,m_grid);
                    prog->runProgram(m_program_boxes[0]); // run main
                    delete prog;
                }
                else if(b->getUtility()==CLEAR){
                    for(ProgramBox* p : m_program_boxes){
                        p->clearActions();
                    }
                }
            }
        }
        // For each program box
        for(ProgramBox* p : m_program_boxes){
            // We check if he clicked on a button
            for(unsigned int i = 0 ; i < p->getActions().size() ; i ++){
                // If he clicked in one, we have to remove it
                if(p->getActions().at(i)->isOverRect(m_mouse)){
                    if(p->getActions().size()!=1){
                        p->deleteAction(i);
                    }else{
                        p->clearActions();
                    }
                }
            }
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
        if(m_selected_button!=nullptr){
            bool found = false;
            unsigned int i =0;
            while(!found && i <m_program_boxes.size()){
                if(m_program_boxes.at(i)->overBox(m_mouse)){

                    // We check ig he put the action between two
                    bool row_found = false;
                    if(m_program_boxes.at(i)->getActions().size()>0){
                        unsigned int row = 0;
                        while(!row_found && row<m_program_boxes.at(i)->getActions().size()){
                            if(m_program_boxes.at(i)->getActions().at(row)->isOverRect(m_mouse)){

                                if((m_selected_button->getAction()==Utils::Action::PROG_P1 && m_program_boxes.at(i)->getType()==Utils::TypeProg::P1)
                                || (m_selected_button->getAction()==Utils::Action::PROG_P2 && m_program_boxes.at(i)->getType()==Utils::TypeProg::P2)
                                || (m_selected_button->getAction()==Utils::Action::PROG_P1 && m_program_boxes.at(i)->getType()==Utils::TypeProg::P2)){
                            std::cout << Utils::getTime() + "[Game-INFO]: Impossible to add an action: it could create an infinite loop" << std::endl;
                                }else{
                                    m_program_boxes.at(i)->addAction(m_selected_button,row);
                                }
                                row_found = true;
                            }else{
                                row ++;
                            }
                        }
                    }
                    if(!row_found){
                        if((m_selected_button->getAction()==Utils::Action::PROG_P1 && m_program_boxes.at(i)->getType()==Utils::TypeProg::P1)
                        || (m_selected_button->getAction()==Utils::Action::PROG_P2 && m_program_boxes.at(i)->getType()==Utils::TypeProg::P2)
                        || (m_selected_button->getAction()==Utils::Action::PROG_P1 && m_program_boxes.at(i)->getType()==Utils::TypeProg::P2)){
                             std::cout << Utils::getTime() + "[Game-INFO]: Impossible to add an action: it could create an infinite loop" << std::endl;
                        }else{
                            m_program_boxes.at(i)->addAction(m_selected_button);
                        }

                    }
                    m_selected_button = nullptr;
                    found = true;
                }else{
                    i ++;
                }
            }
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
            if(m_selected_button->getAction()!=Utils::Action::NONE){
                draw_button_at(*m_selected_button,m_mouse);
            }
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
        // Fix pb avec les label
        b->setLabelText(b->getLabelText());
        b->draw_on(m_window);
    }
}

void Interface::draw_prgm_boxes(std::vector<ProgramBox*> boxes){
    for(ProgramBox* b : boxes){
        b->drawProgBox(m_window);
    }
}

void Interface::draw_button_at(const Button &button, sf::Vector2i pos)
{
    // TODO
    // FINIR
    Button b = Button(button);
    b.setPosition({(float)pos.x,(float)pos.y});
    b.setLabelText(b.getLabelText());
    b.draw_on(m_window);
}

void Interface::draw_background(){
    m_window.draw(m_sprite);
}

// It changes a button appareace according to the mouse position
void Interface::changeButtonAppareance(const bool &onButton, Button* b){
    // Check if it is a action button. If so, it does not apply any theme
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
        image = "menu-lightbot.png";
        break;
    case Utils::State::CREDITS:
        image = "default.png";
        break;
    case Utils::State::LEVEL_SELECTION:
        image = "level-selection.png";
        break;
    case Utils::State::IN_GAME:
        image = "in-game-background3.png";
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
    if(!m_texture.loadFromFile(Utils::IMG_PATH+image)){
        std::cout << Utils::getTime() + "[Texture-ERROR]: Could not load the background" << std::endl;
        std::cout << Utils::getTime() + "[Texture-FIX]: Check \""
                     + Utils::IMG_PATH + "\"" << std::endl;
        std::cout << Utils::getTime() + "[Texture-FIX]: The texture will be ignored." << std::endl;
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
