//    This file is part of LightBot.
//
//    LightBot is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    Foobar is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with LightBot.  If not, see <http://www.gnu.org/licenses/>.

#include "Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size, int id)
    : m_id {id}
{
    m_button.setSize(size);
    m_button.setPosition(position);
    m_button.setFillColor(sf::Color::Red);
    m_button.setOrigin(size.x-size.x/2., size.y-size.y/2.);

}

bool Button::overRect(sf::Vector2i mousePos, sf::RectangleShape button)
{
    return mousePos.x >= button.getPosition().x - button.getSize().x/2
            && mousePos.x <= button.getPosition().x + button.getSize().x - button.getSize().x/2
            && mousePos.y >= button.getPosition().y - button.getSize().y/2
            && mousePos.y <= button.getPosition().y + button.getSize().y - button.getSize().y/2;
}

void Button::setColor(sf::Color color)
{
    m_button.setFillColor(color);
}

int Button::getId()
{
    return m_id;
}


sf::RectangleShape Button::button()
{
    return m_button;
}

void Button::draw_on(sf::RenderWindow &window)
{
    window.draw(m_button);
}
