/* FILE: Page.cpp
 * Page class implementation.
 */

#include "gui/Page.h"


void Page::addDrawing(sf::Drawable& drawable) {
    m_drawings.push_back(&drawable);
}



