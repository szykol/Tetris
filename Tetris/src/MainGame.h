#pragma once

#include <States/State.h>
#include <GUI/TextBox.h>

#include "Grid.h"
#include "Shape.h"

class MainGame : public sen::State {
    sen::TextBox info;    
    Grid m_grid;
    float gravityDeltaTime = 0.f;
    float movementDeltaTime = 0.f;
    static sf::Vector2f s_gridTopLeft;
    std::unique_ptr<Shape> m_shape;
public:
    MainGame();

    virtual void update(sf::RenderWindow& window) override;
    virtual void update(float deltaTime, sf::RenderWindow& window) override;
    virtual void handleEvents(sf::Event& evnt) override;
    virtual void render(sf::RenderTarget& target) override;
    virtual void input(sf::RenderWindow& window) override;

    inline static const sf::Vector2f& getGridTopLeft() {return s_gridTopLeft;}
};