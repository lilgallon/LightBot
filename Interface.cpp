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

#include "Interface.h"
#include "Utils.h"

namespace {
    const unsigned int SCREEN_WIDTH = 1280;
    const unsigned int SCREEN_HEIGHT = 720;

    const sf::Vector2f ACTION_BUTTON_SIZE = {80,80};

    const sf::Vector2f PROGRAM_BOX_SIZE_MAIN = {360,218};
    const sf::Vector2f PROGRAM_BOX_POS_MAIN  = {SCREEN_WIDTH-PROGRAM_BOX_SIZE_MAIN.x-20,35};

    const sf::Vector2f PROGRAM_BOX_SIZE_P = {PROGRAM_BOX_SIZE_MAIN.x,145};

    const sf::Vector2f PROGRAM_BOX_POS_P1 = {SCREEN_WIDTH-PROGRAM_BOX_SIZE_MAIN.x-20,35+PROGRAM_BOX_SIZE_MAIN.y+40};
    const sf::Vector2f PROGRAM_BOX_POS_P2 = {PROGRAM_BOX_POS_P1.x,PROGRAM_BOX_POS_P1.y+PROGRAM_BOX_SIZE_P.y+40};
    const sf::Color    PROGRAM_BOX_COLOR  = sf::Color(128,128,128,128);
    const sf::Color    PROGRAM_BOX_OUTCOL = sf::Color::Black;
    const int          PROGRAM_BOX_OUTTHI = 2;

    const int RUN   = 1;
    const int CLEAR = 2;
    const int RETRY = 3;
    const int BACK  = 4;

    const sf::Vector2f END_SCREEN_TEXT_POS  = {(float)SCREEN_WIDTH/3,(float)SCREEN_HEIGHT/3};
    const sf::Color    END_SCREEN_TEXT_COL  = sf::Color(255,255,255);
    const std::string  END_SCREEN_TEXT_FONT = "coolvetica.ttf";
    const sf::Color    END_SCREEN_BACK_COL  = sf::Color(128,128,128,150);

    const sf::Vector2f GRID_POS_ON_LEVEL_SELECTION = {250,350};

    const std::string  LEVEL_SELECTION_ID = "1";

    const int EXECUTION_DELAY_MICRO_SEC = 800000;
    // 800 000 us = 800 ms = 0.8 sec

}

/************************************************
*         CONSTRUCTORS / DESTRUCTORS            *
*************************************************/
// It initializes the buttons, the initial game state
Interface::Interface()
    : Application {SCREEN_WIDTH, SCREEN_HEIGHT, L"Lightbot"}, m_state {Utils::State::HOME}, m_first_loop{true}, m_program_end_screen{false},  m_selected_level{-1}, m_selected_button{nullptr},m_grid{new Grid()},m_robot{new Robot()}
{



    // IDEE
    // Une optimisation, si nécesasire, serait de ne charger que les boutons correspondant à
    // l'état du jeu dans lequel on est. Là, on charge tous les boutons du jeu entier en un coup
    // Bien evidemment, ce serait utile uniquement si il y a bp de lag en jeu mais ça devrait pas


    Theme *defaultTheme = new Theme(1);
    Theme *actionTheme = new Theme(2);
    m_themes.push_back(defaultTheme);
    m_themes.push_back(actionTheme);


    // HOME BUTTONS
    Button* play = new Button(Utils::State::LEVEL_SELECTION,{(float)SCREEN_WIDTH/2.-90/2, (float)SCREEN_HEIGHT/2-50/2}     , {90, 50} , defaultTheme, "Play");
    Button* credits = new Button(Utils::State::CREDITS,{(float)SCREEN_WIDTH/2.-90/2, (float)SCREEN_HEIGHT/2+50/2+10} , {90, 50}, defaultTheme, "Credits");
    m_buttons_home.push_back(play);
    m_buttons_home.push_back(credits);

    // LEVEL SELECTION BUTTONS
    Button* back_to_menu = new Button(Utils::State::HOME,{(float)SCREEN_WIDTH/2-80/2-20, (float)SCREEN_HEIGHT-50-20}, {80, 50}, defaultTheme, "Back");
    Button* go_to_editor = new Button(Utils::State::LEVEL_EDITOR, {(float)SCREEN_WIDTH/2+80/2+20, (float)SCREEN_HEIGHT-50-20} , {80, 50}, defaultTheme, "Editor");
    m_buttons_level_selection.push_back(back_to_menu);
    m_buttons_level_selection.push_back(go_to_editor);

    // CREDITS BUTTONS
    Button* back_from_credits = new Button(Utils::State::HOME,{(float)SCREEN_WIDTH/25, (float)SCREEN_HEIGHT/20}, {50, 50}, defaultTheme, "<-");
    m_buttons_credits.push_back(back_from_credits);

    // CREDITS BUTTONS
    Button* back_from_editor = new Button(Utils::State::LEVEL_SELECTION,{(float)SCREEN_WIDTH/25, (float)SCREEN_HEIGHT/20}, {50, 50}, defaultTheme, "<-");
    m_buttons_editor.push_back(back_from_editor);

    // IN_GAME BUTTONS
    Button* forward = new Button(Utils::Action::FORWARD,{40+ACTION_BUTTON_SIZE.x+(ACTION_BUTTON_SIZE.x+10)*0,SCREEN_HEIGHT-ACTION_BUTTON_SIZE.y/2-20},ACTION_BUTTON_SIZE,actionTheme);
    Button* jump = new Button(Utils::Action::JUMP,{40+ACTION_BUTTON_SIZE.x+(ACTION_BUTTON_SIZE.x+10)*1,SCREEN_HEIGHT-ACTION_BUTTON_SIZE.y/2-20},ACTION_BUTTON_SIZE,actionTheme);
    Button* light = new Button(Utils::Action::LIGHT,{40+ACTION_BUTTON_SIZE.x+(ACTION_BUTTON_SIZE.x+10)*2,SCREEN_HEIGHT-ACTION_BUTTON_SIZE.y/2-20},ACTION_BUTTON_SIZE,actionTheme);
    Button* p_one = new Button(Utils::Action::PROG_P1,{40+ACTION_BUTTON_SIZE.x+(ACTION_BUTTON_SIZE.x+10)*3,SCREEN_HEIGHT-ACTION_BUTTON_SIZE.y/2-20},ACTION_BUTTON_SIZE,actionTheme);
    Button* p_two = new Button(Utils::Action::PROG_P2,{40+ACTION_BUTTON_SIZE.x+(ACTION_BUTTON_SIZE.x+10)*4,SCREEN_HEIGHT-ACTION_BUTTON_SIZE.y/2-20},ACTION_BUTTON_SIZE,actionTheme);
    Button* clockwise = new Button(Utils::Action::TURN_CLOCKWISE,{40+ACTION_BUTTON_SIZE.x+(ACTION_BUTTON_SIZE.x+10)*5,SCREEN_HEIGHT-ACTION_BUTTON_SIZE.y/2-20},ACTION_BUTTON_SIZE,actionTheme);
    Button* counterclock = new Button(Utils::Action::TURN_COUNTERCLOCK,{40+ACTION_BUTTON_SIZE.x+(ACTION_BUTTON_SIZE.x+10)*6,SCREEN_HEIGHT-ACTION_BUTTON_SIZE.y/2-20},ACTION_BUTTON_SIZE,actionTheme);

    Button* run_prgm = new Button(RUN,{SCREEN_WIDTH/(float)1.11, SCREEN_HEIGHT/(float)1.05} , {150, 50}, defaultTheme, "RUN");
    Button* clear_prgms = new Button(CLEAR,{SCREEN_WIDTH/(float)1.3, SCREEN_HEIGHT/(float)1.05} , {150, 50}, defaultTheme, "CLEAR");
    Button* back_to_selection = new Button(BACK,{SCREEN_WIDTH/(float)1.48, SCREEN_HEIGHT/(float)1.05} , {50, 50}, defaultTheme, "<-");

    m_buttons_in_game.push_back(forward);
    m_buttons_in_game.push_back(jump);
    m_buttons_in_game.push_back(light);
    m_buttons_in_game.push_back(p_one);
    m_buttons_in_game.push_back(p_two);
    m_buttons_in_game.push_back(clockwise);
    m_buttons_in_game.push_back(counterclock);

    m_buttons_in_game.push_back(run_prgm);
    m_buttons_in_game.push_back(clear_prgms);
    m_buttons_in_game.push_back(back_to_selection);

    // PROGRAM BOXES
    ProgramBox* prgm_main = new ProgramBox(PROGRAM_BOX_POS_MAIN,PROGRAM_BOX_SIZE_MAIN,PROGRAM_BOX_COLOR,PROGRAM_BOX_OUTCOL,PROGRAM_BOX_OUTTHI,"Main",Utils::TypeProg::MAIN);
    ProgramBox* prgm_p1 = new ProgramBox(PROGRAM_BOX_POS_P1,PROGRAM_BOX_SIZE_P,PROGRAM_BOX_COLOR,PROGRAM_BOX_OUTCOL,PROGRAM_BOX_OUTTHI,"P1",Utils::TypeProg::P1);
    ProgramBox* prgm_p2 = new ProgramBox(PROGRAM_BOX_POS_P2,PROGRAM_BOX_SIZE_P,PROGRAM_BOX_COLOR,PROGRAM_BOX_OUTCOL,PROGRAM_BOX_OUTTHI,"P2",Utils::TypeProg::P2);

    m_program_boxes.push_back(prgm_main);
    m_program_boxes.push_back(prgm_p1);
    m_program_boxes.push_back(prgm_p2);

    // The grid needs a robot before putting a grid on it
    // because loading a level (a grid) will use the robot
    // instance (to update it with level infos)
    m_grid->setRobot(m_robot);

    // END EXECUTION BUTTONS
    Button* retry = new Button(RETRY,{SCREEN_WIDTH/2-70,SCREEN_HEIGHT/2},{100,50},defaultTheme,"RETRY");
    Button* back = new Button(BACK,{SCREEN_WIDTH/2+70, SCREEN_HEIGHT/2},{120,50},defaultTheme,"GO BACK");

    m_buttons_end_program.push_back(retry);
    m_buttons_end_program.push_back(back);

    // END SCREEN TEXT (message you failed / you won ...)
    m_end_screen_text.setPosition(END_SCREEN_TEXT_POS);
    m_end_screen_text.setColor(END_SCREEN_TEXT_COL);

    if (!m_end_screen_font.loadFromFile(Utils::FONT_PATH+END_SCREEN_TEXT_FONT)) {
        std::cout << Utils::getTime() + "[Interface-ERROR]: Could not load the font of end level message" << std::endl;
        std::cout << Utils::getTime() + "[Interface-FIX]: Check \"" + Utils::FONT_PATH+END_SCREEN_TEXT_FONT + "\"" << std::endl;
        std::cout << Utils::getTime() + "[Interface-FIX]: The font will be ignored." << std::endl;

    }else{
        m_end_screen_text.setFont(m_end_screen_font);
        std::cout << Utils::getTime() + "[Interface-INFO]: Font loaded" << std::endl;
    }
}

// It deletes the pointers that are contained in the buttons arrays and themes arrays
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
        draw_buttons(m_buttons_home);
        break;
    case Utils::State::CREDITS:
        draw_buttons(m_buttons_credits);
        break;
    case Utils::State::LEVEL_SELECTION:
        if(m_first_loop){
            m_grid->loadLevel(LEVEL_SELECTION_ID);
            // Save level would have been used for the level editor
            // It is possible to try if it is working there
            // m_grid->saveLevel("99","testage");
        }

        draw_buttons(m_buttons_level_selection);
        m_grid->drawGrid(m_window, GRID_POS_ON_LEVEL_SELECTION);
        break;
    case Utils::State::IN_GAME:
        if(m_first_loop){
            // Load the selected level
            m_grid->loadLevel(m_selected_level);
        }

        draw_buttons(m_buttons_in_game);

        m_grid->drawGrid(m_window, {-1,-1});
        draw_prgm_boxes(m_program_boxes);

        // After the execution of the program, there are few more component to be displayed
        if(m_program_end_screen){
            // The rect is the background
            sf::RectangleShape rect;
            rect.setSize({SCREEN_WIDTH,SCREEN_HEIGHT});
            rect.setFillColor(sf::Color(128,128,128,150));
            rect.setPosition(0,0);

            // Draws the background, text, buttons
            m_window.draw(rect);
            m_window.draw(m_end_screen_text);
            draw_buttons(m_buttons_end_program);
        }
        break;
    case Utils::State::LEVEL_EDITOR:
        draw_buttons(m_buttons_editor);
        break;
    case Utils::State::END_GAME:
        break;
    case Utils::State::IDLE:

        break;
    default:
        break;
    }

    // first loop is used to init things
    // (load level, load background according to the gamestate ...)
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
            // Changes the state according to the state
            // indicated by the button pressed
            buttonChangeState(isOnButton(b),b);
        }
        break;
    case Utils::State::CREDITS:
        for(Button * b : m_buttons_credits){
            buttonChangeState(isOnButton(b),b);
        }
        break;
    case Utils::State::LEVEL_SELECTION:
        for(Button * b : m_buttons_level_selection){
            buttonChangeState(isOnButton(b),b);
        }
        if(m_grid->isOverCell(m_mouse)){
            // if we found a cell where the mouse is,
            // we change the selected cell
            changeSelectedCell();
            // And we start the game (change game state)
            changeGameState(Utils::State::IN_GAME);
        }
        break;
    case Utils::State::IN_GAME:
        if(m_program_end_screen){

            // END SCREEN (after executing the programs)

            for(Button* b : m_buttons_end_program){
                // We do things according to the button pressed (retry / back)
                if(b->isOverRect(m_mouse)){

                    if(b->getUtility()==RETRY){
                        // Go out from this special screen
                        m_program_end_screen = false;
                        // Load the actual level (reset robot pos / cell lighting)
                        m_grid->loadLevel(m_selected_level);

                    }else if(b->getUtility()==BACK){
                        // Go out from this screen
                        m_program_end_screen = false;
                        // Load the level selection grid
                        m_grid->loadLevel(LEVEL_SELECTION_ID);
                        // Reset the program boxes
                        for(ProgramBox* b : m_program_boxes){
                            b->clearActions();
                        }
                        // Change the game state 6> go to level selection
                        changeGameState(Utils::State::LEVEL_SELECTION);
                    }
                }
            }

        }else{
            for(Button * b : m_buttons_in_game){
                // If the mouse is on the run program button
                if(b->isOverRect(m_mouse)){
                    if(b->getUtility()==RUN ){

                        /*************************/
                        /*  Execute the program  */
                        /*************************/

                        // Create a new instance of ProgramHandler
                        ProgramHandler* prog = new ProgramHandler(m_program_boxes[0],m_program_boxes[1],m_program_boxes[2],m_robot,m_grid);
                        // Executes it and gets the result
                        int result = executeProgram(prog);
                        // -4 = ALL CELLS ARE NOT TURNED ON
                        // -3 = FAILED (cell way too high)
                        // -2 = FAILED (had to jump)
                        // -1 = FAILED (out of the grid)
                        // 0 = IT'S FINE FOR THE MOMENT (MAIN)
                        // 1 = IT'S FINE FOR THE MOMENT (PROGRAM 1)
                        // 2 = IT'S FINE FOR THE MOMENT (PROGRAM 2)
                        // 3 = WON!
                        // Deletes the prog
                        delete prog;

                        /*************************/
                        /*  Threat the result    */
                        /*************************/

                        // Display the end screen
                        m_program_end_screen = true;
                        // Sets the message according to the result
                        std::string end_screen_message = "";
                        switch (result) {
                        case -4:
                            end_screen_message = "Failed! Not all the cells are turned on.";
                            break;
                        case -3:
                            end_screen_message = "Failed! Had to jump very high...";
                            break;
                        case -2:
                            end_screen_message = "Failed! Had to jump.";
                            break;
                        case -1:
                            end_screen_message = "Failed! Out of the grid.";
                            break;
                        case 3:
                            end_screen_message = "Level finished! Well done.";
                            break;
                        default:
                            end_screen_message = "Failed! Unknown reason.";
                            break;
                        }
                        m_end_screen_text.setString(end_screen_message);
                    }

                    else if(b->getUtility()==CLEAR){
                        // Clear the buttons from the program boxes
                        for(ProgramBox* p : m_program_boxes){
                            p->clearActions();
                        }
                    }

                    else if(b->getUtility()==BACK){
                        for(ProgramBox* b : m_program_boxes){
                            b->clearActions();
                        }
                        m_grid->loadLevel(LEVEL_SELECTION_ID);
                        changeGameState(Utils::State::LEVEL_SELECTION);
                    }
                }
            }

            // We are here because he clicked, then, we have to check if he clicked on
            // a button from any program boxes, we will have to remove this action if so
            for(ProgramBox* p : m_program_boxes){
                for(unsigned int i = 0 ; i < p->getActions().size() ; i ++){
                    // We check if he clicked on a button
                    if(p->getActions().at(i)->isOverRect(m_mouse)){
                        // If he clicked in one, we have to remove it
                        if(p->getActions().size()!=1){
                            p->deleteAction(i);
                        }else{
                            // We call clearAction() if there is only one action, because
                            // deleteAction(row) make a left decal, and if there is only one
                            // it would crash "out of range"
                            p->clearActions();
                        }
                    }
                }
            }
        }

        // Get the selected button (if there is one selected) to move it later
        m_selected_button = getSelectedButton();
        break;
    case Utils::State::LEVEL_EDITOR:
        for(Button * b : m_buttons_editor){
            buttonChangeState(isOnButton(b),b);
        }
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
        if(!m_program_end_screen){

            // In this "if", we will check if the user has selected a button
            // Since we are in "button released", we have to check if the mouse
            // is in a program box. In this case, we have to add an action to the
            // programbox
            if(m_selected_button!=nullptr){
                bool found = false;
                unsigned int i =0;
                while(!found && i <m_program_boxes.size()){
                    if(m_program_boxes.at(i)->overBox(m_mouse)){

                        /*********************************************/
                        /* We check if he put the action between two */
                        /*********************************************/

                        // Note: the algorithm gets the row by checking if the action is released
                        // on an other action. In this case, we put the action BEFORE the action
                        // which the user one was on

                        bool row_found = false;
                        // We check if there is an action already, otherwise, we won't put the action between two
                        if(m_program_boxes.at(i)->getActions().size()>0){
                            // We are here because we found the program box where the user want to add his action
                            unsigned int row = 0;
                            while(!row_found && row<m_program_boxes.at(i)->getActions().size()){

                                if(m_program_boxes.at(i)->getActions().at(row)->isOverRect(m_mouse)){
                                    // We are here because we found the action on which the user want to put his action

                                    // This "if" is here to check if the user did not put P1 in P1 or P2 in P2 or P1 on P2
                                    // We decided to not handle the infinite loop..
                                    if((m_selected_button->getAction()==Utils::Action::PROG_P1 && m_program_boxes.at(i)->getType()==Utils::TypeProg::P1)
                                            || (m_selected_button->getAction()==Utils::Action::PROG_P2 && m_program_boxes.at(i)->getType()==Utils::TypeProg::P2)
                                            || (m_selected_button->getAction()==Utils::Action::PROG_P1 && m_program_boxes.at(i)->getType()==Utils::TypeProg::P2)){
                                        std::cout << Utils::getTime() + "[Game-INFO]: Impossible to add an action: it could create an infinite loop" << std::endl;
                                    }else{
                                        // If all is okay, we can add his action at the row defined before
                                        m_program_boxes.at(i)->addAction(m_selected_button,row);
                                    }
                                    row_found = true;
                                }else{
                                    row ++;
                                }
                            }
                        }
                        if(!row_found){
                            // If we are there it is because the user did not released it's action on an other one
                            // ndlr: he want to put his action at the end

                            // This "if" is here to check if the user did not put P1 in P1 or P2 in P2 or P1 on P2
                            // We decided to not handle the infinite loop..
                            if((m_selected_button->getAction()==Utils::Action::PROG_P1 && m_program_boxes.at(i)->getType()==Utils::TypeProg::P1)
                                    || (m_selected_button->getAction()==Utils::Action::PROG_P2 && m_program_boxes.at(i)->getType()==Utils::TypeProg::P2)
                                    || (m_selected_button->getAction()==Utils::Action::PROG_P1 && m_program_boxes.at(i)->getType()==Utils::TypeProg::P2)){
                                std::cout << Utils::getTime() + "[Game-INFO]: Impossible to add an action: it could create an infinite loop" << std::endl;
                            }else{
                                // If all is okay, we add the action
                                m_program_boxes.at(i)->addAction(m_selected_button);
                            }

                        }
                        // The selected button changes to null!
                        m_selected_button = nullptr;
                        found = true;
                    }else{
                        i ++;
                    }
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
    // If the mouse was released, we have to set the selected button to false anyway
    m_selected_button = nullptr;
}

// Make things when the player moves his mouse
void Interface::mouse_moved(){
    switch (m_state) {
    case Utils::State::HOME:
        for(Button * b : m_buttons_home){
            // Changes the button appareace if the mouse is a the button
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
        // Changes the cell lighting according to the mouse (level selection)
        m_grid->isOverCell(m_mouse);
        break;
    case Utils::State::IN_GAME:
        if(m_program_end_screen){
            for(Button* b : m_buttons_end_program){
                changeButtonAppareance(isOnButton(b),b);
            }
        }else{
            for(Button * b : m_buttons_in_game){
                changeButtonAppareance(isOnButton(b),b);
            }
        }
        break;
    case Utils::State::LEVEL_EDITOR:
        for(Button * b : m_buttons_editor){
            changeButtonAppareance(isOnButton(b),b);
        }
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
        if(!m_program_end_screen){
            // We display the selected button at the cursor position
            // if an action is selected and the mouse is ghettign pressed
            if(m_selected_button!=nullptr){
                if(m_selected_button->getAction()!=Utils::Action::NONE){
                    draw_button_at(*m_selected_button,m_mouse);
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
}

/************************************************
*        DRAWING / UPDATE METHODS                *
*************************************************/
// It draws the buttons of the actual game state
void Interface::draw_buttons(std::vector<Button*> buttons){
    for(Button *b : buttons){
        // This is a fix to a sfml bug which confunds text string
        // with other classes for an unknown reason
        // comment the next line to see..
        b->setLabelText(b->getLabelText());

        // Draws the button
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
    // Draws a button at a specified position (here we use it to draw
    // the selected action on the cursor)
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

    // Changed the button color if onButton is true
    // Used there to change button color with the mouse position
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
        // Get the state aimed by the button
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
        image = "credits.png";
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
        std::cout << Utils::getTime() + "[Texture-FIX]: Check \""+ Utils::IMG_PATH + "\"" << std::endl;
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
    // REMINDER: the level id is built on this template : "xy.txt", we want xy here
    std::string s;
    s = std::to_string((int)m_grid->getOverCell()->getPos().x)
            + std::to_string((int)m_grid->getOverCell()->getPos().y);
    m_selected_level = s;
    std::cout << Utils::getTime() + "[Game-INFO]: Level id #" + s + " selected" << std::endl;
}

void Interface::changeGameState(const Utils::State &s)
{
    std::cout << Utils::getTime() + "[Game State-INFO]: Changing the game state." << std::endl;
    // changes the state
    m_state = s;
    // sets the first loop to true since we changed the gamestate, we will init things
    // according to the game state (ex: loadlevel(x), loadbackground()...)
    m_first_loop = true;
}

Button* Interface::getSelectedButton()
{
    // Gets the selected button, if there is one

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

// Execute the prog and returns the result
// it changes button theme too
// -4 = ALL CELLS ARE NOT TURNED ON
// -3 = FAILED (cell way too high)
// -2 = FAILED (had to jump)
// -1 = FAILED (out of the grid)
// 0 = IT'S FINE FOR THE MOMENT (MAIN)
// 1 = IT'S FINE FOR THE MOMENT (PROGRAM 1)
// 2 = IT'S FINE FOR THE MOMENT (PROGRAM 2)
// 3 = WON!
int Interface::executeProgram(ProgramHandler* prog)
{
    // We start on main, and it is fine for the moment, no problem was met
    int result = 0;

    // If there is no action, it is lost
    if(m_program_boxes[0]->getActions().size()==0)
        return -4;


    unsigned int index_main = 0;
    unsigned int index_p1   = 0;
    unsigned int index_p2   = 0;

    // This loop will remain while there are actions in main & the result is okay (there is no error)
    while(index_main < m_program_boxes[0]->getActions().size() && (result==0 || result ==1 || result ==2)){
        // Gets the result after running the program for the action at index_main
        result = prog->runProgram(m_program_boxes[0],index_main,result,m_themes[1],m_themes[0]);

        // Wait / Display the robot with updated infos
        // No wait if we found P2 or P1 (we are actually checking main)
        if(m_program_boxes[0]->getActions().at(index_main)->getAction() != Utils::Action::PROG_P2
                && m_program_boxes[0]->getActions().at(index_main)->getAction() != Utils::Action::PROG_P1){
            loop();
            m_window.display();
            usleep(EXECUTION_DELAY_MICRO_SEC);
        }

        // If main spotted P1 we check the actions of P1
        if(result == 1){
            index_p1 = 0;
            if(m_program_boxes[1]->getActions().size()!=0){
                while(index_p1<m_program_boxes[1]->getActions().size() && (result == 1 || result == 2)){
                    result = prog->runProgram(m_program_boxes[1],index_p1,result,m_themes[1],m_themes[0]);

                    // No wait if we found P2 (we are actually checking P1)
                    if(m_program_boxes[1]->getActions().at(index_p1)->getAction() != Utils::Action::PROG_P2){
                        loop();
                        m_window.display();
                        usleep(EXECUTION_DELAY_MICRO_SEC);
                    }

                    // if P1 spotted P2 we check the actions of P2
                    if(result == 2){
                        index_p2 = 0;
                        if(m_program_boxes[2]->getActions().size()!=0){
                            while(result == 2 && index_p2<m_program_boxes[2]->getActions().size()){
                                result = prog->runProgram(m_program_boxes[2],index_p2,result,m_themes[1],m_themes[0]);
                                loop();
                                m_window.display();
                                usleep(EXECUTION_DELAY_MICRO_SEC);
                                index_p2 ++;
                            }

                            // If, when we have finished checking the actions, we have result 2
                            // (it means that P2 executed without any problem)
                            // we go back to P1 indicating there is no problem (result = 1)
                            if(result==2){
                                result = 1;
                            }
                        }
                    }
                    m_program_boxes.at(1)->getActions().at(m_program_boxes.at(1)->getActions().size()-1)->setTheme(m_themes[1]);
                     if(m_program_boxes.at(2)->getActions().size()!=0)
                        m_program_boxes.at(2)->getActions().at(m_program_boxes.at(2)->getActions().size()-1)->setTheme(m_themes[1]);

                    index_p1 ++;
                }
                // If, when we have finished checking the actions, we have result 1
                // (it means that P1 executed without any problem)
                // we go back to main indicating there is no problem (result = 0)
                if(result==1){
                    // All was fine until now
                    result = 0;
                }
            }
        }

        // if main spotted P2, we check the actions of p2
        if(result == 2){
            index_p2 = 0;
            if(m_program_boxes[2]->getActions().size()!=0){
                while(result == 2 && index_p2<m_program_boxes[2]->getActions().size()){
                    result = prog->runProgram(m_program_boxes[2],index_p2,result,m_themes[1],m_themes[0]);
                    loop();
                    m_window.display();
                    usleep(EXECUTION_DELAY_MICRO_SEC);
                    index_p2 ++;
                }

                // If, when we have finished checking the actions, we have result 2
                // (it means that P2 executed without any problem)
                // we go back to main indicating there is no problem (result = 0)
                if(result==2){
                    // All was fine until now
                    result = 0;
                }
            }
        }

        index_main ++;
    }


    // We stopped the execution, so the last actions theme were not set to default.
    // We have to set the button theme to default, otherwise it will stay "highlighted"
    m_program_boxes.at(0)->getActions().at(index_main-1)->setTheme(m_themes[1]);
    if(m_program_boxes.at(1)->getActions().size()!=0 && index_p1!=0)
        m_program_boxes.at(1)->getActions().at(index_p1-1)->setTheme(m_themes[1]);
    if(m_program_boxes.at(2)->getActions().size()!=0 && index_p2!=0)
        m_program_boxes.at(2)->getActions().at(index_p2-1)->setTheme(m_themes[1]);

    if(result == 0 || result == 1 || result == 2){
        bool all_cells_are_lighted = true;
        unsigned int i = 0;
        while(all_cells_are_lighted && i<m_grid->getGrid().size()){
            if(!m_grid->getGrid().at(i)->getLight()){
                all_cells_are_lighted = false;
            }else{
                i ++;
            }
        }
        if(all_cells_are_lighted){
            result = 3;
        }else{
            result = -4;
        }
    }
    return result;
}
