#pragma once
#include <vector>

#include <SFML/Graphics.hpp>

#include "Cell.h"

class Grid {
    sf::Vector2u m_size;
    std::vector<Cell> m_grid;
    const sf::Vector2f m_topLeft;

  public:
    Grid(const sf::Vector2u &size, const sf::Vector2f &topLeft);
    void render(sf::RenderTarget &target);
    inline const sf::Vector2u &getSize() const { return m_size; }
};