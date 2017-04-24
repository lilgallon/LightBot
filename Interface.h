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
    Interface();
    ~Interface();
private:

    //enum class State { HOME, CREDITS, LEVEL_SELECTION, IN_GAME, LEVEL_EDITOR, END_GAME, IDLE} m_state;
    Utils::State m_state;

    std::vector<Button*> m_buttons_home;
    std::vector<Button*> m_buttons_level_selection;
    std::vector<Button*> m_buttons_credits;
    std::vector<Theme*> m_themes;
    int m_mouseInRectId;
    bool m_first_loop;

    Grid* m_grid;

    // ELements liés à la boucle de jeu
    void loop()  override;

    // Interactions w/ user
    void mouse_button_pressed()                              override;
    void mouse_button_released()                             override;
    void mouse_moved          ()                             override;
    //void key_pressed (const sf::Event::KeyEvent & /*event*/) override;

    // Interfaces
    void draw_buttons(std::vector<Button*> buttons);
    void draw_screen();

    // Other methods
    bool isOnButton(Button *b);
    void changeButtonAppareance(bool onButton, Button* b);
    void changeState(bool onButton, Button* b);

};

#endif // INTERFACE_H
