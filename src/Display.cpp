/* FILE: Display.cpp
 * Display class implementation.
 */

#include "Display.h"

Display::Display(const std::string title, sf::Vector2f dimensions) {
    display.create(sf::VideoMode(dimensions.x, dimensions.y), title);
}

void Display::draw() {
    display.clear(color);

    /* Display elements here. */

    display.display();
}

void Display::update() {
}

void Display::close() {
}

void Display::setBackgroundColor(sf::Color color) {
    this->color = color;
}
