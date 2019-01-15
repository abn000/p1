#include "Game.hpp"
#include <cstdlib>
#include <algorithm>
#include <random>
#include <iostream>

Game::Game(int board_size = 20, int mines = 50) 
: m_board_size(board_size), m_total_mines(mines), m_window(sf::VideoMode(m_window_size,m_window_size), "My Game")  {
    m_current_size = sf::Vector2f(m_window_size, m_window_size);
    m_font.loadFromFile("font.ttf");

    m_win_msg.setFont(m_font);
    m_win_msg.setCharacterSize(30);
    m_win_msg.setString(L"You win!");
    m_win_msg.setPosition(m_current_size * 0.5f);
    
    m_lose_msg.setFont(m_font);
    m_lose_msg.setCharacterSize(30);
    m_lose_msg.setString(L"You lose!");
    m_lose_msg.setPosition(m_current_size * 0.5f);

    srand(time(0));
    reset();
    run();
}

void Game::reset() {
    won = false;
    lost = false;
    std::vector<Cell*> pool;
    m_board.clear();
    for (int i = 0; i < m_board_size; i++) {
        m_board.push_back(std::vector<Cell>());
        for (int j = 0; j < m_board_size; j++) {
            m_board[i].push_back(Cell());
            m_board[i][j].setPosition(sf::Vector2i(j * Cell::m_cell_size, i * Cell::m_cell_size));
        }
    }
    for (int i = 0; i < m_board_size; i++) {
        for (int j = 0; j < m_board_size; j++) {
            pool.push_back(&m_board[i][j]);
        }
    }
    std::shuffle(pool.begin(), pool.end(), std::default_random_engine(time(0)));
    for (int i = 0; i < m_total_mines; i++) {
        /* std::cerr << "i = " << i << std::endl;
        for (int j = 0; j < m_board_size; j++) {
            std::cerr << "\t";
            for (int k = 0; k < m_board_size; k++) {
                if (pool[i] == &m_board[j][k]) {
                    std::cerr << "X";
                }
                else {
                    if (m_board[j][k].isMine()) {
                        std::cerr << "x";
                    }
                    else {
                        std::cerr << "_";
                    }
                }
            }
            std::cerr << std::endl;
        }
        std::cerr << std::endl << std::endl; */
        if (!pool[i]->isMine()) {
            pool[i]->setMine(true);
        }
        else {
            std::cerr << "Already mine. Shouldn't happen!!" << std::endl;
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
                    if (m_board[y][x].isMine()) {
                        lose();
                    }
                }
                break;
            case sf::Event::Resized:
                m_current_size = sf::Vector2f(e.size.width, e.size.height);
                break;
            case sf::Event::KeyPressed:
                if ((won || lost) && e.key.code == sf::Keyboard::R) {
                    reset();
                } 
                break;
            default:
                break;
            }
        }
        if (to_uncover == 0) {
            win();
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
    if (lost) {
        m_window.draw(m_lose_msg);
    }
    else if (won) {
        m_window.draw(m_win_msg);
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

void Game::lose() {
    uncover_all();
    lost = true;
}

void Game::win() {
    uncover_all();
    won = true;
}

void Game::uncover_all() {
    for (int i = 0; i < m_board_size; i++) {
        for (int j = 0; j < m_board_size; j++) {
            if (m_board[i][j].isCovered()) {
                uncover(j, i);
            }
        }
    }
}