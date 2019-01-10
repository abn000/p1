#include "Game.hpp"
#include <cstdlib>

Game::Game() 
: m_window(sf::VideoMode(m_window_size,m_window_size), "My Game"), m_current_size(sf::Vector2f(m_window_size, m_window_size)) {
    srand(time(0));
    m_font.loadFromFile("font.ttf");
    for (int i = 0; i < m_board_size; i++) {
        for (int j = 0; j < m_board_size; j++) {
            if (rand() % 100 > 70) {
                m_board[i][j].setMine(true);
            }
            m_board[i][j].setPosition(sf::Vector2i(j * Cell::m_cell_size, i * Cell::m_cell_size));
        }
    }

    for (int i = 0; i < m_board_size; i++) {
        for (int j = 0; j < m_board_size; j++) {
            int mines = 0;
            if (j > 0 && i > 0) {
                int x, y;
                x = j - 1;
                y = i - 1;
                if (m_board[y][x].isMine()) {
                    mines++;
                }
            }
            if (j > 0) {
                int x, y;
                x = j - 1;
                y = i;
                if (m_board[y][x].isMine()) {
                    mines++;
                }
            }
            if (j > 0 && i < m_board_size - 1) {
                int x, y;
                x = j - 1;
                y = i + 1;
                if (m_board[y][x].isMine()) {
                    mines++;
                }
            }
            if (i > 0) {
                int x, y;
                x = j;
                y = i - 1;
                if (m_board[y][x].isMine()) {
                    mines++;
                }
            }
            if (i < m_board_size - 1) {
                int x, y;
                x = j;
                y = i + 1;
                if (m_board[y][x].isMine()) {
                    mines++;
                }
            }
            if (j < m_board_size - 1 && i > 0) {
                int x, y;
                x = j + 1;
                y = i - 1;
                if (m_board[y][x].isMine()) {
                    mines++;
                }
            }
            if (j < m_board_size - 1) {
                int x, y;
                x = j + 1;
                y = i;
                if (m_board[y][x].isMine()) {
                    mines++;
                }
            }
            if (j < m_board_size - 1 && i < m_board_size - 1) {
                int x, y;
                x = j + 1;
                y = i + 1;
                if (m_board[y][x].isMine()) {
                    mines++;
                }
            }
            m_board[i][j].setNeighbours(mines);
            m_board[i][j].setFont(&m_font);
        }
    }

    run();
}

void Game::run() {
    while (m_window.isOpen()) {
        sf::Event e;
        while (m_window.pollEvent(e)) {
            switch (e.type) {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::MouseButtonPressed:
                int x, y;
                x = e.mouseButton.x / (Cell::m_cell_size * m_current_size.x / m_window_size);
                y = e.mouseButton.y / (Cell::m_cell_size * m_current_size.y / m_window_size);
                if (m_board[y][x].isCovered()) {
                    uncover(x, y);
                }
                break;
            case sf::Event::Resized:
                m_current_size = sf::Vector2f(e.size.width, e.size.height);
            default:
                break;
            }
        }
        draw();
    }
}

void Game::draw() {
    m_window.clear(sf::Color::White);
    for (int i = 0; i < m_board_size; i++) {
        for (int j = 0; j < m_board_size; j++) {
            m_board[i][j].draw(&m_window);
        }
    }
    m_window.display();
}

void Game::uncover(int x, int y) {
    if (m_board[y][x].isCovered()) {
        m_board[y][x].setCovered(false);
        if (m_board[y][x].getNeighbours() == 0 && !m_board[y][x].isMine()) {
            if (x > 0 && y > 0) {
                uncover(x - 1, y - 1);
            }
            if (x > 0) {
                uncover(x - 1, y);
            }
            if (x > 0 && y < m_board_size - 1) {
                uncover(x - 1, y + 1);
            }
            if (y > 0) {
                uncover(x, y - 1);
            }
            if (y < m_board_size - 1) {
                uncover(x, y + 1);
            }
            if (x < m_board_size - 1 && y > 0) {
                uncover(x + 1, y - 1);
            }
            if (x < m_board_size - 1) {
                uncover(x + 1, y);
            }
            if (x < m_board_size - 1 && y < m_board_size - 1) {
                uncover(x + 1, y + 1);
            }
        }
    }
}