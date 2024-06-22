/* file		main.cpp
 * brief	This file contains the entry point (main-thread).
 */

/* Library includes. */
#include <iostream>
#include <set>
#include <cstring>
#include "DBManager.h"
#include "Student.h"
#include "StudentManager.h"
#include "Display.h"
#include "logger.h"


int main() {
    //TODO: Making a interactive gui to managee student data
    sf::RenderWindow window;
    sf::Vector2f dimensions = {800, 600};
    std::string title = "SSDBMS: Student Database Manager";
    window.create(sf::VideoMode(dimensions.x, dimensions.y), title);

    // Elements
    sf::RectangleShape rec;

    sf::Event event;
    bool running = true;
    while (running) {
        // Polling events;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    running = false;
                    break;

                default:
                    break;
            }
        }

        window.clear(sf::Color::White);
        window.display();
    }
}


