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
#include "ProgramBox.h"
#include "Robot.h"
#include "ProgramHandler.h"

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
    std::vector<Button*> m_buttons_in_game;
    std::vector<Button*> m_buttons_end_program;
    std::vector<Theme*> m_themes;
    std::vector<ProgramBox*> m_program_boxes;
    // Loop controller
    bool m_first_loop;
    bool m_program_end_screen;
    // Selection "tools"
    std::string m_selected_level;
    Button* m_selected_button;
    // TODO
    // make a method / class that loads a level and put it in m_grid
    Grid* m_grid;
    // Texure
    sf::Texture m_texture;
    sf::Sprite m_sprite;

    // RObot!!
    Robot* m_robot;

    sf::Text m_end_screen_text;
    sf::Font m_end_screen_font;

    unsigned int m_step_index;
    bool m_is_in_exectuion;

    /** Methods **/

    // Interactions w/ user
    void mouse_button_pressed()                              override;
    void mouse_button_released()                             override;
    void mouse_moved          ()                             override;
    void mouse_pressing        ()                            override;
    //void key_pressed (const sf::Event::KeyEvent & /*event*/) override;
    // Interfaces
    void draw_buttons(std::vector<Button*> buttons);
    void draw_prgm_boxes(std::vector<ProgramBox*> boxes);
    void draw_button_at(const Button &button, sf::Vector2i pos);
    void draw_background();

    // Other methods
    bool isOnButton(Button *b) const;
    bool isOnCell(Grid* g) const;
    void changeButtonAppareance(const bool &onButton, Button* b);
    void loop()  override;
    void loadBackground();

    void changeSelectedCell();

    void buttonChangeState(const bool &onButton, Button* b);
    void changeGameState(const Utils::State &s);

    Button* getSelectedButton();

    int executeProgram(ProgramHandler *prog);


};

#endif // INTERFACE_H
