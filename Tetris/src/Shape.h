#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include "Cell.h"

class Shape
{
    std::vector<Cell> m_cells;
public:
    enum Type{I = 0, T, O, L, J, S, Z};
    enum Movement{NONE = 0, DOWN, RIGHT, LEFT};
public:
    explicit Shape(Type type, const sf::Vector2u& startPos = sf::Vector2u(0,0));
    void render(sf::RenderTarget& target);
    void applyMovement(Movement movement);
	std::vector<sf::Vector2i> calculateNextPosition(Movement movement);
	inline const std::vector<Cell>& getCells() const { return m_cells; }
};