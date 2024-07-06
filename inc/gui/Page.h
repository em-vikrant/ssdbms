/* FILE: Page.h
 * Header file for the Page class.
 */

#ifndef _PAGE_H_
#define _PAGE_H_

#include <vector>
#include <string>
#include "logger.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"


class Page {
    public:
        Page(const std::string& title, bool status = false)
            : m_title(title), m_status(status) {}
        Page(const std::string& title, sf::Color color, bool status = false)
            : m_title(title), m_color(color), m_status(status) {}

        void setBackgroundColor(const sf::Color& color) { m_color = color; }
        void setTitle(const std::string&& title) { m_title = title; }
        void setStatus(bool status) { m_status = status; }
        void addDrawing(sf::Drawable& drawable);

        bool getStatus() const { return m_status; }
        sf::Color getColor() const { return m_color; }
        sf::Event& getEvent() const { return m_event; }
        std::string getTitle() const { return m_title; }
        std::vector<sf::Drawable*> getDrawings() const { return m_drawings; }

    private:
        sf::Color m_color;
        mutable sf::Event m_event;
        std::string m_title;
        std::vector<sf::Drawable*> m_drawings;
        bool m_status;
};

#endif
