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
    void setTexture(sf::Texture *texture);
    void setLabel(std::string label);
    int getId();

    Button(int id, sf::Vector2f position, sf::Vector2f size, sf::Texture *texture                  );
    Button(int id, sf::Vector2f position, sf::Vector2f size, sf::Color   color                     );
    Button(int id, sf::Vector2f position, sf::Vector2f size, sf::Texture *texture, std::string label);
    Button(int id, sf::Vector2f position, sf::Vector2f size, sf::Color   color   , std::string label);

private:
    void initButton(sf::Vector2f position, sf::Vector2f size, sf::Texture *texture, sf::Color color);
    void initLabel(sf::Vector2f position, sf::Vector2f size, std::string label);

    int m_id;
    sf::RectangleShape m_button;
    sf::Text m_label;
    sf::Font m_font;
};

#endif // BUTTON_H
