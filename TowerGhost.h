#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class TowerGhost {
private:
    sf::Sprite ghost;
public:
    void setSprite(sf::Texture& texture, sf::IntRect rect);
    void updatePosition(sf::Vector2f mousePos);
    void draw(sf::RenderWindow& window);
    bool active = false;
};

