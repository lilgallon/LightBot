#ifndef INTERFACE_H
#define INTERFACE_H

#include "Button.h"
#include "Application.h"
#include "Utils.h"
#include "Grid.h"
#include "ProgramBox.h"
#include "Robot.h"
#include "ProgramHandler.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <unistd.h>

class Interface : public Application
{
public:
    /** Constructors / Desctructors **/
    Interface();
    ~Interface();
private:

    //============= ATTRIBUTES ==============//

    /**************/
    /* Containers */
    /**************/
    // Buttons
    std::vector<Button*> m_buttons_home;
    std::vector<Button*> m_buttons_level_selection;
    std::vector<Button*> m_buttons_credits;
    std::vector<Button*> m_buttons_in_game;
    std::vector<Button*> m_buttons_end_program;
    std::vector<Button*> m_buttons_editor;
    // Themes
    std::vector<Theme*> m_themes;
    // Program boxes
    std::vector<ProgramBox*> m_program_boxes;

    /****************************************************/
    /* Linked to game handler (used to handle the game) */
    /****************************************************/
    // Game state
    Utils::State m_state;
    // Loop specifications (the loop will do differents things according to these attributes)
    bool m_first_loop;
    bool m_program_end_screen;

    /*******************/
    /* Selection tools */
    /*******************/
    std::string m_selected_level;
    Button* m_selected_button;

    /***********************/
    /* Linked to the level */
    /***********************/
    Grid* m_grid;
    Robot* m_robot;

    /***********************/
    /* Linked to the level */
    /***********************/
    // Background
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    // Text of end_screen (when the execution is finished)
    sf::Text m_end_screen_text;
    sf::Font m_end_screen_font;

    //============= METHODS ==============//

    /************************/
    /* Interactions w/ user */
    /************************/
    void mouse_button_pressed()                              override;
    void mouse_button_released()                             override;
    void mouse_moved          ()                             override;
    void mouse_pressing        ()                            override;

    // loop!!!!
    void loop()  override;

    /************************/
    /*    Drawing methods   */
    /************************/
    void draw_buttons(std::vector<Button*> buttons);
    void draw_prgm_boxes(std::vector<ProgramBox*> boxes);
    void draw_button_at(const Button &button, sf::Vector2i pos);
    void draw_background();

    /***********************/
    /*   Utility methods   */
    /***********************/
    // With mouse position
    bool isOnButton(Button *b) const;
    bool isOnCell(Grid* g) const;
    // Update appareance
    void changeButtonAppareance(const bool &onButton, Button* b);
    void loadBackground();
    // Update ?
    void changeSelectedCell();
    // Update state
    void buttonChangeState(const bool &onButton, Button* b);
    void changeGameState(const Utils::State &s);
    // Getter
    Button* getSelectedButton();
    // Execute the program (used to clarify the code)
    int executeProgram(ProgramHandler *prog);
};

#endif // INTERFACE_H
