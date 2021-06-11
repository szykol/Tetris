#include "Grid.h"

Grid::Grid(const sf::Vector2u &size, const sf::Vector2f &topLeft) : m_size(size), m_topLeft(topLeft) {
    const auto elementCount = size.x * size.y;
    m_grid.reserve(elementCount);

    for (uint x = 0; x < size.x; x++) {
        for (uint y = 0; y < size.y; y++) {
            auto cell = Cell(sf::Vector2i(x, y));
            m_grid.push_back(std::move(cell));
        }
    }
}

void Grid::render(sf::RenderTarget &target) {
    for (auto &cell : m_grid)
        cell.render(target);
}
