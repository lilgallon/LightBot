#ifndef PROGRAMBOX_H
#define PROGRAMBOX_H

#include "Utils.h"
#include "Button.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class ProgramBox
{  
private:
    // The container with all the buttons (actions)
    std::vector<Button*> m_actions;

    // This rectangle is used to draw the program box
    sf::RectangleShape m_rect;
    // Program box name to draw
    sf::Font m_font;
    sf::Text m_text;

    // Type of the prog (main, p1, p2)
    Utils::TypeProg m_type_prog;

public:
    ProgramBox(const sf::Vector2f &pos, const sf::Vector2f &size, const sf::Color &fill_color, const sf::Color &outline_color, const int &outline_size, const std::string &prog_name, const Utils::TypeProg &type_prog);
    ~ProgramBox();

    // Actions (add / remove actions in the programbox)
    void addAction(Button *button);
    void addAction(Button *button, const unsigned int &row);
    void deleteAction(const unsigned int &row);
    void clearActions();

    // Calculate the new position of a new action in the program box (-1;1) if there is no more place
    sf::Vector2f calculateNewPosition() const;

    // Returns true if the pos is in the programbox
    bool overBox(const sf::Vector2i &pos) const;

    /* GETTERS */
    std::vector<Button *> getActions() const;
    std::string getName() const;
    Utils::TypeProg getType() const;

    // Drawing method
    void drawProgBox(sf::RenderWindow &window);
};

#endif // PROGRAM_H
