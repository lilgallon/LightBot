#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Graphics.hpp>

class Application
{
public:
    Application(unsigned int w, unsigned int h, const std::wstring & title);
    virtual ~Application() = default;

    // Start the game
    void run();

protected:
    // The screen where everything will be showed on
    sf::RenderWindow m_window;
    // The variable containing the mouse position
    sf::Vector2i     m_mouse;

    // Stop the game
    void stop();

    // We will draw everything here
    virtual void loop() = 0;

    // User interaction
    virtual void mouse_button_pressed () {}
    virtual void mouse_button_released() {}
    virtual void mouse_moved          () {}
    virtual void mouse_pressing       () {}

private:
    // Indicators
    // True if the mouse is being pressed: used to call mouse_pressing()
    bool m_pressing_mouse;
    // True if the game is running: used to call methods while the program is running
    bool m_running;

    // Calls the user interaction method corresponding to the user interaction
    void process_events();
    // Used to change m_mouse with the current mouse curosr position
    void set_mouse_coord(int x, int y);
};

#endif
