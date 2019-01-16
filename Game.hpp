#include "Cell.hpp"
#include <vector>

class Game {
    const int m_board_size;
    const int m_window_size = m_board_size * Cell::m_cell_size;

    const int m_total_mines;

    int to_uncover;
    
    std::vector<std::vector<Cell>> m_board;
    sf::RenderWindow m_window;
    sf::Font m_font;

    sf::Text m_win_msg;
    sf::Text m_lose_msg;

    sf::Vector2f m_current_size;

    bool started;
    bool lost;
    bool won;

    void run();
    void draw();

    void uncover(int, int);

    void lose();
    void win();

    void uncover_all();

    void reset();

    void generate_mines(sf::Vector2i);

    void count_flags(int, int);

public:
    Game(int, int);
};