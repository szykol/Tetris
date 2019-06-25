#include "Shape.h"

#include <functional>

Shape::Shape(Shape::Type type, const sf::Vector2u& startPos)
{
    auto color = sf::Color::Yellow;
    if(type == Type::L)
    {
        m_cells = {Cell(startPos + sf::Vector2u{0,0}), Cell(startPos + sf::Vector2u{0, 1}), Cell(startPos + sf::Vector2u{0, 2}), Cell(startPos + sf::Vector2u{1, 2})};
    }
    else if (type == Type::I)
    {
        m_cells = {Cell(startPos + sf::Vector2u{0,0}), Cell(startPos + sf::Vector2u{0, 1}), Cell(startPos + sf::Vector2u{0, 2}), Cell(startPos + sf::Vector2u{0, 3})};
        color = sf::Color::Red;
    }
    else if (type == Type::J)
    {
        m_cells = {Cell(startPos + sf::Vector2u{1,0}), Cell(startPos + sf::Vector2u{1, 1}), Cell(startPos + sf::Vector2u{1, 2}), Cell(startPos + sf::Vector2u{0, 2})};
        color = sf::Color::Magenta;
    }
    else if (type == Type::O)
    {
        m_cells = {Cell(startPos + sf::Vector2u{0,0}), Cell(startPos + sf::Vector2u{1, 0}), Cell(startPos + sf::Vector2u{1, 1}), Cell(startPos + sf::Vector2u{0, 1})};
        color = sf::Color::Cyan;
    }
    else if (type == Type::T)
    {
        m_cells = {Cell(startPos + sf::Vector2u{0,0}), Cell({1, 0}), Cell({2, 0}), Cell({1, 1})};
        color = sf::Color(222,222,222);
    }
    else if (type == Type::S)
    {
        m_cells = {Cell({0,1}), Cell({1, 1}), Cell({1, 0}), Cell({2, 0})};
        color = sf::Color::Blue;
    }
    else if (type == Type::Z)
    {
        m_cells = {Cell({0,0}), Cell({1, 0}), Cell({1, 1}), Cell({2, 1})};
        color = sf::Color::Green;
    }

    for (auto& cell: m_cells)
    {
        cell.setFillColor(color);
        cell.setOutlineThickness(-2);
    }
}

void Shape::applyMovement(Movement movement)
{
    auto indexVector = sf::Vector2i(0, 0);
    if (movement == Movement::DOWN)
        indexVector = {0, 1};
    else if (movement == Movement::LEFT)
        indexVector = {-1, 0};
    else if (movement == Movement::RIGHT)
        indexVector = {1, 0};

    for (auto& cell: m_cells)
    {
		auto [x, y] = cell.getIndex();
		auto [nextX, nextY] = indexVector;
        cell.setIndex(sf::Vector2i(x + nextX, y + nextY));
    }
}

void Shape::render(sf::RenderTarget& target)
{
    for (auto& cell: m_cells)
        cell.render(target);
}