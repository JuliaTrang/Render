#pragma once
#include <SFML/Graphics.hpp>
#include <iostream> 
#include "LogicGame/Project1/cPlayer.h"

class HUDManager {
private:
    sf::Texture boxTexture;
    sf::Text goldText, moneyText;
    sf::Sprite goldBox, moneyBox;

public:
    void init(sf::Font& font);
    void setValues();
    void draw(sf::RenderWindow& window);
};

