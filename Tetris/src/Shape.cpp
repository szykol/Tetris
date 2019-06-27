#include "Shape.h"

#include <functional>

Shape::Shape(Shape::Type type, const sf::Vector2u& startPos)
    : m_type(type)
{
    auto color = sf::Color::Yellow;
    if(type == Type::L)
    {
        m_cells = {Cell(startPos + sf::Vector2u{0,0}), Cell(startPos + sf::Vector2u{0, 1}), Cell(startPos + sf::Vector2u{0, 2}), Cell(startPos + sf::Vector2u{1, 2})};
		m_pivotIndex = 1;
    }
    else if (type == Type::I)
    {
        m_cells = {Cell(startPos + sf::Vector2u{0,0}), Cell(startPos + sf::Vector2u{0, 1}), Cell(startPos + sf::Vector2u{0, 2}), Cell(startPos + sf::Vector2u{0, 3})};
        color = sf::Color::Red;
		m_pivotIndex = 2;
    }
    else if (type == Type::J)
    {
        m_cells = {Cell(startPos + sf::Vector2u{1,0}), Cell(startPos + sf::Vector2u{1, 1}), Cell(startPos + sf::Vector2u{1, 2}), Cell(startPos + sf::Vector2u{0, 2})};
        color = sf::Color::Magenta;
		m_pivotIndex = 1;
    }
    else if (type == Type::O)
    {
        m_cells = {Cell(startPos + sf::Vector2u{0,0}), Cell(startPos + sf::Vector2u{1, 0}), Cell(startPos + sf::Vector2u{1, 1}), Cell(startPos + sf::Vector2u{0, 1})};
        color = sf::Color::Cyan;
		m_pivotIndex = 0;
    }
    else if (type == Type::T)
    {
        m_cells = {Cell(startPos + sf::Vector2u{0,1}), Cell(startPos + sf::Vector2u{1, 1}), Cell(startPos + sf::Vector2u{2, 1}), Cell(startPos + sf::Vector2u{1, 0})};
        color = sf::Color(222,222,222);
		m_pivotIndex = 1;
    }
    else if (type == Type::S)
    {
        m_cells = {Cell(startPos + sf::Vector2u{0,1}), Cell(startPos + sf::Vector2u{1, 1}), Cell(startPos + sf::Vector2u{1, 0}), Cell(startPos + sf::Vector2u{2, 0})};
        color = sf::Color::Blue;
		m_pivotIndex = 1;
    }
    else if (type == Type::Z)
    {
        m_cells = {Cell(startPos + sf::Vector2u{0,0}), Cell(startPos + sf::Vector2u{1, 0}), Cell(startPos + sf::Vector2u{1, 1}), Cell(startPos + sf::Vector2u{2, 1})};
        color = sf::Color::Green;
		m_pivotIndex = 2;
    }

    for (auto& cell: m_cells)
    {
        cell.setFillColor(color);
        cell.setOutlineThickness(-2);
    }
}

void Shape::applyMovement(Movement movement)
{
	auto nextPos = calculateNextPosition(movement);

	auto posIt = nextPos.begin();
    for (auto& cell: m_cells)
    {
        cell.setIndex(*posIt);
		posIt++;
    }
}

std::vector<sf::Vector2i> Shape::calculateNextPosition(Movement movement)
{
	auto indexVector = sf::Vector2i(0, 0);
	if (movement == Movement::DOWN)
		indexVector = { 0, 1 };
	else if (movement == Movement::LEFT)
		indexVector = { -1, 0 };
	else if (movement == Movement::RIGHT)
		indexVector = { 1, 0 };
    else if (m_type != Type::O && (movement == Movement::ROTATE_LEFT || movement == Movement::ROTATE_RIGHT))
        return calculateRotation(movement);

	std::vector<sf::Vector2i> newPos;
	for (auto& cell : m_cells)
	{
		auto [x, y] = cell.getIndex();
		auto [nextX, nextY] = indexVector;
		newPos.push_back(sf::Vector2i(x + nextX, y + nextY));
	}

	return newPos;
}

std::vector<sf::Vector2i> Shape::calculateRotation(Movement movement)
{
	std::vector<sf::Vector2i> transformations;
	transformations.reserve(4);

	auto pivot = m_cells[m_pivotIndex].getIndex();
	auto px = pivot.x;
	auto py = pivot.y;

	std::function<sf::Vector2i(const Cell&)> fn;
    if (movement == Movement::ROTATE_RIGHT)
    {
		fn = [px, py](auto& c) {
			auto [x1, y1] = c.getIndex();
			auto x2 = (px + py - y1);
			auto y2 = (x1 + py - px);

			return sf::Vector2i(x2, y2);
		};
    }
    else if (movement == Movement::ROTATE_LEFT)
    {
		fn = [px, py](auto& c) {
			auto [x1, y1] = c.getIndex();
			auto x2 = (y1 + px - py);
			auto y2 = (px + py - x1);

			return sf::Vector2i(x2, y2);
		};
    }

	for (auto& c : m_cells)
	{
		transformations.push_back(fn(c));
	}

    return transformations;
}

void Shape::render(sf::RenderTarget& target)
{
    for (auto& cell: m_cells)
        cell.render(target);
}