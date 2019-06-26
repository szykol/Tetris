#include "MainGame.h"

#include <Application.h>
#include <Managers/AudioProvider.h>
#include <Util/Random.h>

#include <iostream>

sf::Vector2f MainGame::s_gridTopLeft = sf::Vector2f(400,0);

MainGame::MainGame()
    : info("You're playing Tetris!"),
	m_grid({ 10, 20 }, s_gridTopLeft)
{
    const auto centerPos = (sf::Vector2f)Application::getInitialWindowSize() / 2.f;
    info.setPosition(centerPos);
    //sen::AudioProvider::get()->playMusic("../res/Sounds/Motivational.wav");

	auto [x, y] = m_grid.getSize();
	for (int i = 0; i < x; i++)
	{
		m_ground.push_back(sf::Vector2u(i, y));
	}

    auto type = sen::Random::get<int>(0, Shape::Type::Z);
    auto posX = (unsigned int)sen::Random::get<int>(0, 10);

    m_shape = std::make_unique<Shape>((Shape::Type)type, sf::Vector2u{posX, 0});
	keepShapeInBounds();
}

void MainGame::update(sf::RenderWindow& window)
{

}

void MainGame::update(float deltaTime, sf::RenderWindow& window)
{
    static const auto gravityTime = 0.2f;
    static const auto moveTime = 0.15f;

    gravityDeltaTime += deltaTime;
    movementDeltaTime += deltaTime;
    if (movementDeltaTime >= moveTime)
    {
		auto move = Shape::Movement::NONE;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            move = Shape::Movement::RIGHT;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            move = Shape::Movement::LEFT;
        
		auto nextIndex = m_shape->calculateNextPosition(move);
		
		auto [inArea, bounds] = nextPositionInArea(nextIndex);
		if (!nextPositionTouchesGround(nextIndex) && inArea)
			m_shape->applyMovement(move);
		
        movementDeltaTime -= moveTime;
    }
    if (gravityDeltaTime > gravityTime)
    {
		auto nextIndex = m_shape->calculateNextPosition(Shape::Movement::DOWN);
		auto gridSize = m_grid.getSize();

		if (nextPositionTouchesGround(nextIndex))
			spawnNewShape();
			
		m_shape->applyMovement(Shape::Movement::DOWN);
        gravityDeltaTime -= gravityTime;
    }  
}

bool MainGame::nextPositionTouchesGround(const std::vector<sf::Vector2i>& nextIndex)
{
	for (auto &nextIndexCell: nextIndex)
	{
		for (auto &groundCell: m_ground)
		{
			if (groundCell.getIndex() == nextIndexCell)
				return true;
		}
	}
	return false;
}

std::tuple<bool,MainGame::AreaBounds> MainGame::nextPositionInArea(const std::vector<sf::Vector2i>& nextIndex)
{
	auto gridSize = m_grid.getSize();
	for (auto &nextIndexCell: nextIndex)
	{
		if (nextIndexCell.x < 0)
			return std::make_tuple(false, AreaBounds::LEFT);
		else if (nextIndexCell.x >= gridSize.x)
			return std::make_tuple(false, AreaBounds::RIGHT);
	}
	return std::make_tuple(true, AreaBounds::NONE);
}

void MainGame::keepShapeInBounds()
{
	auto currentCells = m_shape->getCells();

	std::vector<sf::Vector2i> cellIndices; 
	std::transform( currentCells.begin(), currentCells.end(), std::back_inserter( cellIndices ), [](const Cell& c) {
		return c.getIndex();
	});

	while(true)
	{
		auto [inArea, bounds] = nextPositionInArea(cellIndices);
		if (inArea)
			break;
		
		if (bounds == AreaBounds::LEFT)
			m_shape->applyMovement(Shape::Movement::RIGHT);
		else if (bounds == AreaBounds::RIGHT)
			m_shape->applyMovement(Shape::Movement::LEFT);

		cellIndices.clear();
		currentCells = m_shape->getCells();
		std::transform(currentCells.begin(), currentCells.end(), std::back_inserter(cellIndices), [](const Cell& c) {
			return c.getIndex();
		});
	}
}

void MainGame::spawnNewShape()
{
	auto shapeCells = m_shape->getCells();
	m_ground.insert(m_ground.end(), shapeCells.begin(), shapeCells.end());

	auto type = sen::Random::get<int>(0, Shape::Type::Z);
	auto posX = sen::Random::get<unsigned int>(0, 10);

	m_shape = std::make_unique<Shape>((Shape::Type)type, sf::Vector2u{ posX, 0 });
	keepShapeInBounds();
}

void MainGame::handleEvents(sf::Event& evnt)
{
}

void MainGame::render(sf::RenderTarget& target)
{
    auto& window = Application::getWindow();
    info.render(window);

    m_grid.render(window);

	for (auto& groundCell : m_ground) {
		groundCell.render(target);
	}
    m_shape->render(window);
}

void MainGame::input(sf::RenderWindow& window)
{
}
