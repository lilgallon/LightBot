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
}

Interface::Interface()
    :Application {SCREEN_WIDTH, SCREEN_HEIGHT, L"Lightbot"}, m_first_loop{true}
{
    // IDEE
    // Une optimisation, si nécesasire, serait de ne charger que les boutons correspondant à
    // l'état du jeu dans lequel on est. Là, on charge tous les boutons du jeu entier en un coup
    // Bien evidemment, ce serait utile uniquement si il y a bp de lag en jeu mais ça devrait pas


    Theme *defaultTheme = new Theme(1);
    m_themes.push_back(defaultTheme);

    Button* home1 = new Button(Utils::State::LEVEL_SELECTION,{(float)SCREEN_WIDTH/2, SCREEN_HEIGHT/(float)1.8}     , {90, 70} , defaultTheme);
    Button* home2 = new Button(Utils::State::CREDITS,{SCREEN_WIDTH/(float)1.11, SCREEN_HEIGHT/(float)1.05} , {150, 50}, defaultTheme);
    m_buttons_home.push_back(home1);
    m_buttons_home.push_back(home2);

    Button* levelSelection1 = new Button(Utils::State::HOME,{(float)SCREEN_WIDTH/25, (float)SCREEN_HEIGHT/20}, {50, 50}, defaultTheme);
    m_buttons_level_selection.push_back(levelSelection1);

    Button* credits1 = new Button(Utils::State::HOME,{(float)SCREEN_WIDTH/25, (float)SCREEN_HEIGHT/20}, {50, 50}, defaultTheme);
    m_buttons_credits.push_back(credits1);

    m_state = Utils::State::HOME;
}

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

/**
 * Interface::run()
 * ouverture de la fenêtre et boucle d'interaction
 */
void Interface::loop()
{
    m_window.clear(sf::Color::White);
    switch(m_state){
    case Utils::State::HOME:
        draw_buttons(m_buttons_home);
        break;
    case Utils::State::CREDITS:
        draw_buttons(m_buttons_credits);
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
        m_first_loop = false;
        m_grid->drawGrid(m_window);
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
    m_window.display();
}

void Interface::draw_buttons(std::vector<Button*> buttons){
    for(Button *b : buttons){
        b->draw_on(m_window);
    }
}

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

void Interface::mouse_button_released(){

}

void Interface::changeButtonAppareance(bool onButton, Button* b){
    if(onButton){
        b->setColor(b->getTheme()->getRectOnRectFillColor());
        b->setOutlineColor(b->getTheme()->getRectOnRectOutlineColor());
    }else{
        b->setColor(b->getTheme()->getRectDefaultFillColor());
        b->setOutlineColor(b->getTheme()->getRectDefaultOutlineColor());
    }
}

void Interface::changeState(bool onButton, Button* b){
    if(onButton){
       std::cout << Utils::getTime() + "[Game State-INFO]: Changing the game state." << std::endl;
        m_state = b->getState();
    }
}

bool Interface::isOnButton(Button* b){
    return b->isOverRect(m_mouse);
}

bool Interface::isOnCell(Grid* g){
    return g->isOverCell(m_mouse);
}
