#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>

class Button
{
public:
    sf::RectangleShape button();
    void draw_on(sf::RenderWindow & window);
    bool overRect(sf::Vector2i mousePos, sf::RectangleShape button);
    void setColor(sf::Color color);
    int getId();

    Button(sf::Vector2f position, sf::Vector2f size, int id);
private:
    int m_id;
    sf::RectangleShape m_button;
};

#endif // BUTTON_H
