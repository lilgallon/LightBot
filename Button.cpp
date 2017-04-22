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
