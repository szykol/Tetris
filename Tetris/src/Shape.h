#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include "Cell.h"

class Shape
{
public:
    enum Type{I = 0, T, O, L, J, S, Z};
    enum Movement{NONE = 0, DOWN, RIGHT, LEFT, ROTATE_RIGHT, ROTATE_LEFT};
private:
	std::vector<Cell> m_cells;
    Type m_type;
	int m_pivotIndex = 1;
public:
    explicit Shape(Type type, const sf::Vector2u& startPos = sf::Vector2u(0,0));
    void render(sf::RenderTarget& target);
    void applyMovement(Movement movement);
	std::vector<sf::Vector2i> calculateNextPosition(Movement movement);
	inline const std::vector<Cell>& getCells() const { return m_cells; }
private:
    std::vector<sf::Vector2i> calculateRotation(Movement movement);
};