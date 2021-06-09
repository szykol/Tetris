#include "MainGame.h"

#include "ScoreState.h"

#include <Skeleton/Application.h>
#include <Skeleton/Managers/AudioProvider.h>
#include <Skeleton/Managers/StateManager.h>
#include <Skeleton/GUI/Popup.h>
#include <Skeleton/Util/Random.h>

#include <iostream>

sf::Vector2f MainGame::s_gridTopLeft = sf::Vector2f(400, 0);

MainGame::MainGame() : m_score(0), m_scoreBox("Your Score: 0"), m_grid({10, 20}, s_gridTopLeft) {
    m_scoreBox.setFitTextSize(true);
    auto sizeX = Application::getInitialWindowSize().x;
    m_scoreBox.setPosition(sizeX - 200, 200);
    // sen::AudioProvider::get()->playMusic("../res/Sounds/Motivational.wav");

    auto [x, y] = m_grid.getSize();
    for (int i = 0; i < x; i++) {
        m_ground.push_back(sf::Vector2i(i, y));
    }

    spawnNewShape();
    keepShapeInBounds();
}

void MainGame::update(sf::RenderWindow &window) {}

void MainGame::update(float deltaTime, sf::RenderWindow &window) {
    static auto gravityTime = 0.5f;
    static const auto rotateTime = 0.35f;
    static const auto moveTime = 0.1f;

    gravityDeltaTime += deltaTime;
    movementDeltaTime += deltaTime;
    rotateDeltaTime += deltaTime;
    if (movementDeltaTime >= moveTime) {
        auto move = Shape::Movement::NONE;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            move = Shape::Movement::RIGHT;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            move = Shape::Movement::LEFT;

        auto nextIndex = m_shape->calculateNextPosition(move);
        auto [inArea, bounds] = nextPositionInArea(nextIndex);

        if (!nextPositionTouchesGround(nextIndex)) {
            if (inArea) {
                m_shape->applyMovement(move);
                movementDeltaTime = 0.f;
            }
        }
    }

    if (rotateDeltaTime >= rotateTime) {

        auto move = Shape::Movement::NONE;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            move = Shape::Movement::ROTATE_RIGHT;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            move = Shape::Movement::ROTATE_LEFT;

        auto nextIndex = m_shape->calculateNextPosition(move);
        auto [inArea, bounds] = nextPositionInArea(nextIndex);

        if (!nextPositionTouchesGround(nextIndex))
            if (move == Shape::Movement::ROTATE_LEFT || move == Shape::Movement::ROTATE_RIGHT) {
                m_shape->applyMovement(move);
                keepShapeInBounds();
                rotateDeltaTime = 0.f;
            }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        gravityTime = 0.1f;
    else
        gravityTime = 0.5f;

    if (gravityDeltaTime > gravityTime) {
        auto nextIndex = m_shape->calculateNextPosition(Shape::Movement::DOWN);
        auto gridSize = m_grid.getSize();

        if (nextPositionTouchesGround(nextIndex)) {
            shapeToGround();
            spawnNewShape();
            clearGround();
        }

        m_shape->applyMovement(Shape::Movement::DOWN);
        gravityDeltaTime = 0.f;
    }

    m_scoreBox.getTextObject().setString("Your Score: " + std::to_string(m_score));
}

bool MainGame::nextPositionTouchesGround(const std::vector<sf::Vector2i> &nextIndex) {
    for (auto &nextIndexCell : nextIndex) {
        for (auto &groundCell : m_ground) {
            if (groundCell.getIndex() == nextIndexCell)
                return true;
        }
    }
    return false;
}

std::tuple<bool, MainGame::AreaBounds> MainGame::nextPositionInArea(const std::vector<sf::Vector2i> &nextIndex) {
    auto gridSize = m_grid.getSize();
    for (auto &nextIndexCell : nextIndex) {
        if (nextIndexCell.x < 0)
            return std::make_tuple(false, AreaBounds::LEFT);
        else if (nextIndexCell.x >= gridSize.x)
            return std::make_tuple(false, AreaBounds::RIGHT);
    }
    return std::make_tuple(true, AreaBounds::NONE);
}

void MainGame::keepShapeInBounds() {
    auto currentCells = m_shape->getCells();

    std::vector<sf::Vector2i> cellIndices;
    std::transform(currentCells.begin(), currentCells.end(), std::back_inserter(cellIndices),
                   [](const Cell &c) { return c.getIndex(); });

    while (true) {
        auto [inArea, bounds] = nextPositionInArea(cellIndices);
        if (inArea)
            break;

        if (bounds == AreaBounds::LEFT)
            m_shape->applyMovement(Shape::Movement::RIGHT);
        else if (bounds == AreaBounds::RIGHT)
            m_shape->applyMovement(Shape::Movement::LEFT);

        cellIndices.clear();
        currentCells = m_shape->getCells();
        std::transform(currentCells.begin(), currentCells.end(), std::back_inserter(cellIndices),
                       [](const Cell &c) { return c.getIndex(); });
    }
}

void MainGame::pullTheGround(int y) {
    std::for_each(m_ground.begin(), m_ground.end(), [y](auto &c) {
        auto [prevX, prevY] = c.getIndex();
        if (prevY <= y) {
            c.setIndex({prevX, prevY + 1});
        }
    });
}

void MainGame::spawnNewShape() {
    auto type = sen::Random::get<int>(0, Shape::Type::Z);
    auto posX = sen::Random::get<unsigned int>(0, 10);

    m_shape = std::make_unique<Shape>((Shape::Type)type, sf::Vector2i{int(posX), -2});
    keepShapeInBounds();

    auto currentCells = m_shape->getCells();

    std::vector<sf::Vector2i> cellIndices;
    std::transform(currentCells.begin(), currentCells.end(), std::back_inserter(cellIndices),
                   [](const Cell &c) { return c.getIndex(); });

    if (nextPositionTouchesGround(cellIndices)) {
        sen::StateManager::pushState(std::make_unique<ScoreState>(m_score));
    }
}

void MainGame::shapeToGround() {
    auto shapeCells = m_shape->getCells();
    m_ground.insert(m_ground.end(), shapeCells.begin(), shapeCells.end());
}

void MainGame::clearGround() {
    auto groundCount = 0;
    for (int y = m_grid.getSize().y - 1; y >= 0;) {
        auto pred = [&y](auto &c) { return c.getIndex().y == y; };
        auto count = std::count_if(m_ground.begin(), m_ground.end(), pred);
        if (count == m_grid.getSize().x) {
            m_ground.erase(std::remove_if(m_ground.begin(), m_ground.end(), pred), m_ground.end());
            pullTheGround(y);
            groundCount++;
        } else {
            y--;
        }
    }

    if (groundCount == 1)
        m_score += 40;
    else if (groundCount == 2)
        m_score += 100;
    else if (groundCount == 3)
        m_score += 300;
    else if (groundCount >= 4)
        m_score += 1200;
}

void MainGame::handleEvents(sf::Event &evnt) {}

void MainGame::render(sf::RenderTarget &target) {
    target.clear(sf::Color::Black);

    m_grid.render(target);

    for (auto &groundCell : m_ground) {
        groundCell.render(target);
    }
    m_shape->render(target);
    m_scoreBox.render(target);
}

void MainGame::input(sf::RenderWindow &window) {}
