#include <SFML/Graphics.hpp>

class Cell {
    bool m_covered;
    bool m_mine;
    bool m_flagged;
    int m_neighbours;
    int m_neighbour_flags;

    sf::RectangleShape m_shape;
    sf::Font* m_font;

    sf::Text m_text;

    sf::Vector2i m_position;

public:

    const static int m_cell_size = 40;

    Cell();
    bool isCovered();
    bool isMine();
    bool isFlagged();
    int getNeighbours();
    int getNeighFlags();

    void setMine(bool);
    void setNeighbours(int);
    void setNeighFlags(int);
    void setCovered(bool);
    void setFlagged(bool);
    void setPosition(sf::Vector2i);

    void setFont(sf::Font*);

    void draw(sf::RenderWindow*);
};