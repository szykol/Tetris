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
}

void MainGame::update(sf::RenderWindow& window)
{

}

void MainGame::update(float deltaTime, sf::RenderWindow& window)
{
    static const auto gravityTime = 1.f;
    static const auto moveTime = 0.15f;

    gravityDeltaTime += deltaTime;
    movementDeltaTime += deltaTime;
    if (movementDeltaTime >= moveTime)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            m_shape->applyMovement(Shape::Movement::RIGHT);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            m_shape->applyMovement(Shape::Movement::LEFT);
        
        movementDeltaTime -= moveTime;
    }
    if (gravityDeltaTime > gravityTime)
    {
		auto nextPos = m_shape->calculateNextPosition(Shape::Movement::DOWN);
		
		auto gridSize = m_grid.getSize();

		for (auto& cell : nextPos)
		{
			for (auto& groundCell : m_ground)
			{
				if (!m_hitGround && cell == groundCell.getIndex())
				{
					std::cout << "Shape has hit the Ground!" << std::endl;

					auto shapeCells = m_shape->getCells();
					m_ground.insert(m_ground.end(), shapeCells.begin(), shapeCells.end());
					
					m_hitGround = true;

					auto type = sen::Random::get<int>(0, Shape::Type::Z);
					auto posX = sen::Random::get<unsigned int>(0, 10);

					m_shape = std::make_unique<Shape>((Shape::Type)type, sf::Vector2u{ posX, 0 });
				}
			}
		}

		m_hitGround = false;
		m_shape->applyMovement(Shape::Movement::DOWN);
        gravityDeltaTime -= gravityTime;
    }  
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
