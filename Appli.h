#ifndef APPLI_H
#define APPLI_H
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>


class Appli
{
public:
    Appli();
    void loop();
private:
    const unsigned int SCREEN_WIDTH = 800;
    const unsigned int SCREEN_HEIGHT = 600;

    enum{ HOME, CREDITS, LEVEL_SELECTION, IN_GAME, LEVEL_EDITOR, END_GAME, IDLE} m_gameState;

    sf::Vector2i m_mouse;
    std::vector<Button> m_buttonsHome;
    std::vector<Button> m_buttonsLevelSelection;
    std::vector<Button> m_buttonsCredits;
    sf::RenderWindow m_window;
    bool m_running;
    int m_mouseInRectId;

    std::vector<Button> choseButton();
    sf::Vector2i getMousePos();
    int getButton();
    void processEvents();
    void drawScreen();
};

#endif // APPLI_H
