/* FILE: Board.cpp
 * Board class implementation.
 */

#include "gui/Board.h"


Board::Board(sf::Vector2f dimesions, std::string boardTitle) {
    m_canvas.create(sf::VideoMode(800, 600), boardTitle);
    m_dimensions = dimesions;
}

void
Board::paste(const std::shared_ptr<Page>& pPage) {
    m_currPage = pPage;
}

void
Board::show() {
    sf::Event& event = m_currPage->getEvent();

    while (m_canvas.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                m_currPage->setStatus(false);
                break;
            
            default:
                break;
        }
    }

    m_canvas.clear(m_currPage->getColor());

    for (auto drawing : m_currPage->getDrawings()) {
        m_canvas.draw(*drawing);
    }

    m_canvas.display();
}

