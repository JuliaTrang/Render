#pragma once
#include <SFML/Graphics.hpp>

class Scene {
public:
    virtual ~Scene() {}

    virtual void handleEvent(sf::Event& event, sf::RenderWindow& window) = 0;
    virtual void update(sf::RenderWindow& window, float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual bool isDone() const = 0;
    virtual int getNextState() const = 0;
};
