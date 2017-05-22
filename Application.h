#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Graphics.hpp>

// TODO CHANGE TO ENG
/*
 * Classe abstraite qui fournit un modèle de comportement
 * pour les applications qui en héritent
 *
 * Elle lance la boucle lecture des evenements/affichage,
 * assure le décodage des eévènements et exécute
 * les fonctions mouse_button_pressed, etc. qui sont
 * (re) définies dans les sous-classes, ainsi que
 * (design pattern comportemental : "patron de méthodes")
 */

class Application
{
public:
    Application(unsigned int w, unsigned int h,
                const std::wstring & title);
    void run();
    virtual ~Application()               = default;

    // Interaction indicator (true if the mouse is being pressed)
    bool m_pressing_mouse;

protected:
    /*
     * les variables accessibles par les sous-classes
     */
    sf::RenderWindow m_window;           // fenêtre de dessin
    sf::Vector2i         m_mouse;            // position de la souris

    // fonctions accessibles
    void stop();

    // fonctions à surcharger

    // affichage sur m_window (obligatoire)
    virtual void loop()                                 = 0;
    // initialisations avant le lancement de la boucle
    virtual void init()                                  {}

    // divers traitements d'évenements
    virtual void mouse_button_pressed ()                 {}
    virtual void mouse_button_released()                 {}
    virtual void mouse_moved          ()                 {}
    virtual void mouse_pressing       ()                 {}

    virtual void key_pressed (const sf::Event::KeyEvent & /*event*/) {}

private:
    bool m_running;

    void process_events();               // traitement des evenements
    void set_mouse_coord(int x, int y);  // releve coord souris
};

#endif // APPLICATION_H
