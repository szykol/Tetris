#include "Cell.h"

#include "../States/MainGame.h"

Cell::Cell(const sf::Vector2i& index)
    : m_gridIndex(index)
{
    setSize({CELLSIZE, CELLSIZE});
    setOutlineThickness(-0.5);
    setOutlineColor(sf::Color(128,128,128));
    setFillColor(sf::Color::Black);
    resetPosition();
}

void Cell::resetPosition()
{
    const auto pos = sf::Vector2f(m_gridIndex.x * CELLSIZE, m_gridIndex.y * CELLSIZE);
    setPosition(pos + MainGame::getGridTopLeft());
}

void Cell::render(sf::RenderTarget& target) 
{
    target.draw(*this);
}

void Cell::setIndex(const sf::Vector2i& index) 
{
    m_gridIndex = index;
    resetPosition();
}