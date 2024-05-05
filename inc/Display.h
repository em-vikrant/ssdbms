/* FILE: Display.h
 * Header file for the Display class.
 */

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Display {
    public:
        Display(const std::string title, sf::Vector2f dimesions);

        void draw();
        void update();
        void close();

        /* Setters. */
        void setBackgroundColor(sf::Color color);

        bool pollEvent(sf::Event& event) { return display.pollEvent(event); }

    private:
        sf::RenderWindow display;
        sf::Vector2f dimensions;
        sf::Color color;
};

#endif
