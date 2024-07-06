/* FILE: Board.h
 * Header file for the Board class. This class will act as a Canvas for the GUI windows.
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include <memory>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "logger.h"
#include "gui/Page.h"


class Board {
    public:
        Board(sf::Vector2f dimesions, std::string boardTitle);

        void paste(const std::shared_ptr<Page>& pPage);
        void show();

    private:
        sf::RenderWindow m_canvas;
        sf::Vector2f m_dimensions;
        std::shared_ptr<Page> m_currPage;
};

#endif
