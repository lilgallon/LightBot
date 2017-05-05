#ifndef INTERFACE_H
#define INTERFACE_H
#include "Button.h"
#include "Application.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

#include "Utils.h"
#include "Grid.h"

class Interface : public Application
{
public:
    /** Constructors / Desctructors **/
    Interface();
    ~Interface();
private:

    /** Attributes **/

    // Game state
    Utils::State m_state;
    // Buttons
    std::vector<Button*> m_buttons_home;
    std::vector<Button*> m_buttons_level_selection;
    std::vector<Button*> m_buttons_credits;
    std::vector<Theme*> m_themes;
    // Loop controller
    bool m_first_loop;
    // Grid (level)
    // TODO
    // make a method / class that loads a level and put it in m_grid
    Grid* m_grid;
    // Texure
    sf::Texture m_texture;
    sf::Sprite m_sprite;

    /** Methods **/
    // Interactions w/ user
    void mouse_button_pressed()                              override;
    void mouse_button_released()                             override;
    void mouse_moved          ()                             override;
    //void key_pressed (const sf::Event::KeyEvent & /*event*/) override;
    // Interfaces
    void draw_buttons(std::vector<Button*> buttons);
    void draw_background();

    // Other methods
    bool isOnButton(Button *b) const;
    bool isOnCell(Grid* g) const;
    void changeButtonAppareance(const bool &onButton, Button* b);
    void changeState(const bool &onButton, Button* b);
    void loop()  override;
    void loadBackground();

};

#endif // INTERFACE_H
