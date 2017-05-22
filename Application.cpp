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

#include "Application.h"


Application::Application(unsigned int w, unsigned int h,
                     const std::wstring & title )
    : m_pressing_mouse{false}, m_window { {w, h}, title}
{
}

void Application::stop() {
    m_running = false;
}

void Application::run()
{
    m_window.setFramerateLimit(60);
    m_running = true;

    init();
    while (m_running) {  // voir
        process_events();
        loop();
        if(m_pressing_mouse){
            mouse_pressing();
        }
        m_window.display();
    }
}

void Application::process_events()
{
    if (! m_window.isOpen()) {
        stop();
        return;
    }

    sf::Event event;

    while (m_window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed :
            stop();
            break;
        case sf::Event::KeyPressed :
            key_pressed(event.key);
            break;
        case sf::Event::MouseButtonPressed :
            // bouton = event.mouseButton.button;
            m_pressing_mouse = true;
            set_mouse_coord(event.mouseButton.x, event.mouseButton.y);
            mouse_button_pressed();
            break;
        case sf::Event::MouseButtonReleased :   
            m_pressing_mouse = false;
            // bouton = event.mouseButton.button;
            set_mouse_coord(event.mouseButton.x, event.mouseButton.y);
            mouse_button_released();
            break;
        case sf::Event::MouseMoved :
            set_mouse_coord(event.mouseMove.x, event.mouseMove.y);
            mouse_moved();
            break;
        default:
            break;
        }
    }
}

/*
 * mémorisation de la position de la souris,
 * avec conversion de coordonnées  pixel -> fenetre
 */
void Application::set_mouse_coord(int x, int y)
{
    auto pos = m_window.mapPixelToCoords( {x, y});
    m_mouse = { pos.x, pos.y };
}