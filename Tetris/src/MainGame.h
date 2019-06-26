#pragma once

#include <States/State.h>
#include <GUI/TextBox.h>

#include "Grid.h"
#include "Shape.h"
#include "Cell.h"

#include <tuple>

class MainGame : public sen::State {
    sen::TextBox info;    
    Grid m_grid;
    float gravityDeltaTime = 0.f;
    float movementDeltaTime = 0.f;
    static sf::Vector2f s_gridTopLeft;
    std::unique_ptr<Shape> m_shape;
	std::vector<Cell> m_ground;

	bool m_hitGround = false;

    enum AreaBounds {NONE = 0, LEFT, RIGHT};
public:
    MainGame();

    virtual void update(sf::RenderWindow& window) override;
    virtual void update(float deltaTime, sf::RenderWindow& window) override;
    virtual void handleEvents(sf::Event& evnt) override;
    virtual void render(sf::RenderTarget& target) override;
    virtual void input(sf::RenderWindow& window) override;

    inline static const sf::Vector2f& getGridTopLeft() {return s_gridTopLeft;}
    bool nextPositionTouchesGround(const std::vector<sf::Vector2i>& nextPosition);
    std::tuple<bool,AreaBounds> nextPositionInArea(const std::vector<sf::Vector2i>& nextPosition);
    void keepShapeInBounds();
    void spawnNewShape();
};