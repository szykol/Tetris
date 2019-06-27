#include <SFML/Graphics.hpp>

#include "Application.h"
#include "Managers/StateManager.h"
#include "Menu.h"
#include "Managers/CacheSystem.h"

#include <memory>

#include "MainGame.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Tetris");
	window.setFramerateLimit(0U);

	Application::init(&window);
	sen::StateManager::switchBackButton(false);
	auto temp = std::make_unique<MenuState>();
	sen::StateManager::pushState(std::move(temp));
	Application::run();

    return 0;	
}
