#pragma once

#include <Skeleton/States/State.h>
#include <Skeleton/GUI/TextBox.h>
#include <Skeleton/Managers/ButtonController.h>

class ScoreState : public sen::State {
    sen::TextBox m_textBox;
    sen::ButtonController m_bc;

  public:
    explicit ScoreState(int score = 0);

    virtual void update(sf::RenderWindow &window) override;
    virtual void update(float deltaTime, sf::RenderWindow &window) override;
    virtual void handleEvents(sf::Event &evnt) override;
    virtual void render(sf::RenderTarget &target) override;
    virtual void input(sf::RenderWindow &window) override;
};
