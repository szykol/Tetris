#include "ScoreState.h"

#include <string>
#include <Skeleton/Application.h>
#include <Skeleton/Managers/StateManager.h>
#include <Skeleton/Managers/ButtonController.h>

#include "MainGame.h"

ScoreState::ScoreState(int score) : m_textBox("Your score is: " + std::to_string(score)) {
    sen::StateManager::switchBackButton(false);

    auto [x, y] = (sf::Vector2f)Application::getInitialWindowSize() / 2.f;
    m_textBox.setPosition(x, y - 200);

    auto restartButton = std::make_shared<sen::Button>("Restart");
    restartButton->setOnClickCallback([] { sen::StateManager::pushState<MainGame>(); });

    auto quitButton = std::make_shared<sen::Button>("Quit");
    quitButton->setOnClickCallback([] { Application::exit(); });

    m_bc.pushButtons(restartButton, quitButton);
    m_bc.setButtonFixedSize(sf::Vector2f(200, 50));
    m_bc.placeButtons();
}

void ScoreState::update(sf::RenderWindow &window) {}

void ScoreState::update(float deltaTime, sf::RenderWindow &window) { m_bc.update(deltaTime); }

void ScoreState::handleEvents(sf::Event &evnt) {}

void ScoreState::render(sf::RenderTarget &target) {
    m_textBox.render(target);
    m_bc.render(target);
}

void ScoreState::input(sf::RenderWindow &window) {}
