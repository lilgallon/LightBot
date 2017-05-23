#ifndef PROGRAMBOX_H
#define PROGRAMBOX_H
#include <vector>
#include "Utils.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <string>

class ProgramBox
{  
private:
    std::vector<Button*> m_actions;

    // THis rectangle is used to draw the program box
    sf::RectangleShape m_rect;
    sf::Font m_font;
    sf::Text m_text;
    Utils::TypeProg m_type_prog;

public:
    ProgramBox(sf::Vector2f pos, sf::Vector2f size, sf::Color fill_color, sf::Color outline_color, int outline_size, std::string prog_name, Utils::TypeProg type_prog);
    ~ProgramBox();

    // Actions
    void addAction(Button *button);
    void addAction(Button *button, const unsigned int &row);
    void deleteAction(const unsigned int &row);
    void clearActions();

    // POsition helper
    sf::Vector2f calculateNewPosition() const;

    bool overBox(sf::Vector2i pos) const;

    std::vector<Button *> getActions() const;
    std::string getName() const;
    Utils::TypeProg getType() const;

    // Graphic
    void drawProgBox(sf::RenderWindow &window);
};

#endif // PROGRAM_H
