#include "Cell.hpp"

Cell::Cell() : m_covered(true), m_mine(false), m_neighbours(-1), m_shape(sf::Vector2f(m_cell_size - 4,m_cell_size - 4)), m_font(NULL) {
    m_shape.setFillColor(sf::Color::Blue);
    m_shape.setOutlineColor(sf::Color::Black);
    m_shape.setOutlineThickness(2.f);
    m_shape.setPosition((sf::Vector2f)m_position + sf::Vector2f(2.f,2.f));
    m_text.setPosition((sf::Vector2f)m_position + sf::Vector2f(2.f,2.f));
    m_text.setFillColor(sf::Color::Black);
    m_text.setStyle(sf::Text::Style::Bold);
    m_text.setCharacterSize(20);
}

bool Cell::isCovered() {
    return m_covered;
}

bool Cell::isMine() {
    return m_mine;
}

int Cell::getNeighbours() {
    return m_neighbours;
}

void Cell::setCovered(bool covered) {
    m_covered = covered;
    if (!covered) {
        if (!m_mine) {
            m_shape.setFillColor(sf::Color::Green);
        }
        else {
            m_shape.setFillColor(sf::Color::Red);
        }
    }
}

void Cell::setMine(bool mine) {
    m_mine = mine;
}

void Cell::setNeighbours(int neighbours) {
    m_neighbours = neighbours;
}

void Cell::setPosition(sf::Vector2i pos) {
    m_position = pos;
    m_shape.setPosition((sf::Vector2f)pos + sf::Vector2f(2.f,2.f));
    m_text.setPosition((sf::Vector2f)pos);
}

void Cell::setFont(sf::Font* font) {
    m_font = font;
    m_text.setFont(*font);
    m_text.setString(sf::String((char)(m_neighbours + 0x30)));
}

void Cell::draw(sf::RenderWindow* window) {
    window->draw(m_shape);
    if (!m_covered && !m_mine && m_neighbours != 0) {
        window->draw(m_text);
    }
}