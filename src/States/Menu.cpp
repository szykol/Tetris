#include "Menu.h"

#include <Skeleton/Managers/StateManager.h>
#include <Skeleton/GUI/Prompt.h>
#include <Skeleton/GUI/Popup.h>
#include <Skeleton/Application.h>

#include "MainGame.h"

MenuState::MenuState() : m_info("TETRIS") {
    auto &window = Application::getWindow();

    auto [x, y] = (sf::Vector2f)Application::getInitialWindowSize() / 2.f;
    m_info.setPosition(x, y - 200);
    m_info.setCharacterSize(45U);

    std::shared_ptr<sen::Button> pushState = std::make_shared<sen::Button>("PLAY");
    std::shared_ptr<sen::Button> quit = std::make_shared<sen::Button>("QUIT");

    quit->setOnClickCallback([this, &window] {
        m_prompt = std::make_shared<sen::Prompt>(sen::PromptStyle::BINARY, "Are you sure?");
        m_prompt->setPosition(sf::Vector2f(Application::getInitialWindowSize()) / 2.f);
        sen::StateManager::pushPrompt(m_prompt);
        m_prompt->setOnResponseCallback([&](const sen::Response &r) {
            if (r.response == sen::Response::TRUE) {
                Application::exit();
            }
        });
    });

    pushState->setOnClickCallback([&window, this] { sen::StateManager::pushState<MainGame>(); });

    m_buttonController.pushButtons(pushState, quit);
    m_buttonController.placeButtons();
    m_buttonController.setButtonFixedSize(sf::Vector2f(185.f, 50.f));
}
void MenuState::update(float deltaTime, sf::RenderWindow &window) { m_buttonController.update(deltaTime); }
void MenuState::render(sf::RenderTarget &target) {
    m_info.render(target);
    m_buttonController.render(target);
}
MenuState::~MenuState() {}
