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

#include "Appli.h"

Appli::Appli()
{
    m_buttonsHome.push_back({           LEVEL_SELECTION, {(float)SCREEN_WIDTH/2, SCREEN_HEIGHT/(float)1.8}     , {90, 70}  , sf::Color::Blue,"Oui1"           }); // Totaly not bobfix
    m_buttonsHome.push_back({           CREDITS        , {SCREEN_WIDTH/(float)1.11, SCREEN_HEIGHT/(float)1.05} , {150, 50} , sf::Color::Blue, "Go back"        });
    m_buttonsLevelSelection.push_back({ HOME           , {(float)SCREEN_WIDTH/25, (float)SCREEN_HEIGHT/20}     , {50, 50}  , sf::Color::Red , "Oui2"           });
    m_buttonsCredits.push_back({        HOME           , {(float)SCREEN_WIDTH/25, (float)SCREEN_HEIGHT/20}     , {50, 50}  , sf::Color::Yellow, "oui3"         });
    m_gameState = HOME;
}

/**
 * Appli::run()
 * ouverture de la fenêtre et boucle d'interaction
 */
void Appli::loop()
{
    m_window.create(sf::VideoMode {SCREEN_WIDTH, SCREEN_HEIGHT, 32},
                    "Light Bot",
                    sf::Style::Close
                    );
    m_window.setFramerateLimit(20);

    m_running = true;
    while (m_running) {
        processEvents();
        drawScreen();
    }
}

std::vector<Button> Appli::choseButton()
{
    std::vector<Button> buttons;

    if (m_gameState == HOME)
    {
        buttons = m_buttonsHome;
    }
    else if (m_gameState == LEVEL_SELECTION)
    {
        buttons = m_buttonsLevelSelection;
    }
    else if (m_gameState == CREDITS)
    {
        buttons = m_buttonsCredits;
    }

    return buttons;
}

sf::Vector2i Appli::getMousePos()
{
    return m_mouse = sf::Mouse::getPosition(m_window);
}

int Appli::getButton()
{
    int buttonRect = IDLE;

    for(Button & bouton : choseButton())
    {
        if(bouton.overRect(getMousePos(), bouton.button()))
        {
            buttonRect = bouton.getId();
        }
    }
    return buttonRect;
}

void Appli::processEvents()
{    
    sf::Event event;
    while(m_window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed :
            m_running = false;
            break;
        case sf::Event::MouseButtonPressed:
            m_mouseInRectId = getButton();
            break;
        case sf::Event::MouseButtonReleased:
            if(m_mouseInRectId == getButton())
            {
                switch (m_mouseInRectId) {
                case HOME:
                    std::cout << "home" << std::endl;
                    m_gameState = HOME;
                    break;
                case CREDITS:
                    std::cout << "credits" << std::endl;
                    m_gameState = CREDITS;
                    break;
                case LEVEL_SELECTION:
                    std::cout << "level_selection" << std::endl;
                    m_gameState = LEVEL_SELECTION;
                    break;
                case IDLE:
                    std::cout << "idle" << std::endl;
                    break;
                }
            }
        default:
            break;
        }
    }
}

void Appli::drawScreen()
{
    m_window.clear(sf::Color::White);

    for(Button & bouton : choseButton())
    {
        if (bouton.overRect(getMousePos(), bouton.button()))
        {
            bouton.setColor(sf::Color::Black);
        }/*
        else
            bouton.setColor(sf::Color::Red);*/
        bouton.draw_on(m_window);
    }
    m_window.display();
}
