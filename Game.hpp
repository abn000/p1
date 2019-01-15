#include "Cell.hpp"
#include <vector>

class Game {
    const int m_board_size;
    const int m_window_size = m_board_size * Cell::m_cell_size;
    
    std::vector<std::vector<Cell>> m_board;
    sf::RenderWindow m_window;
    sf::Font m_font;

    sf::Vector2f m_current_size;

    void run();
    void draw();

    void uncover(int, int);

public:
    Game(int);
};