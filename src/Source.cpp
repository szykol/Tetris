#include <SFML/Graphics.hpp>

#include <Skeleton/Application.h>
#include <Skeleton/Managers/StateManager.h>
#include <Skeleton/Managers/CacheSystem.h>

#include "States/Menu.h"

#include <memory>

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Tetris");
    window.setFramerateLimit(0U);

    Application::init(&window);
    auto backgroundImage = sen::CacheSystem::getCustomResource<sf::Texture>("Images/tet.jpg");
    Application::setBackgroundImage(*backgroundImage);
    auto temp = std::make_unique<MenuState>();
    sen::StateManager::pushState(std::move(temp));
    Application::run();

    return 0;
}
