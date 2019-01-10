#include "Cell.hpp"

class Game {
    const static int m_board_size = 20;
    const static int m_window_size = m_board_size * Cell::m_cell_size;
    
    Cell m_board[m_board_size][m_board_size];
    sf::RenderWindow m_window;
    sf::Font m_font;

    sf::Vector2f m_current_size;

    void run();
    void draw();

    void uncover(int, int);

public:
    Game();
};