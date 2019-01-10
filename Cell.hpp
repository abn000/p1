#include <SFML/Graphics.hpp>

class Cell {
    bool m_covered;
    bool m_mine;
    int m_neighbours;

    sf::RectangleShape m_shape;
    sf::Font* m_font;

    sf::Text m_text;

    sf::Vector2i m_position;

public:

    const static int m_cell_size = 40;

    Cell();
    bool isCovered();
    bool isMine();
    int getNeighbours();

    void setMine(bool);
    void setNeighbours(int);
    void setCovered(bool);
    void setPosition(sf::Vector2i);

    void setFont(sf::Font*);

    void draw(sf::RenderWindow*);
};