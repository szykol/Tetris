#pragma once

#include <SFML/Graphics.hpp>

#define CELLSIZE 40

class Cell : public sf::RectangleShape
{
    sf::Vector2i m_gridIndex;
public:
    Cell(const sf::Vector2i &index);
    void render(sf::RenderTarget& target);
    void setIndex(const sf::Vector2i& index);
    inline const sf::Vector2i getIndex() const { return m_gridIndex; }
private:
    void resetPosition();
};