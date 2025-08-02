#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;

class TowerSelector {
private:
    std::vector<sf::Sprite> towerIcons;
    std::vector<sf::Sprite> towerBox;
public:
    void init(sf::Texture& textureTower, sf::Texture& textureBox);
    int handleClick(sf::Vector2f mousePos);
    void draw(sf::RenderWindow& window);
};

