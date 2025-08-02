#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "TileMap.h"
#include "HUDManager.h"
#include "TowerSelection.h"
#include "TowerGhost.h" 
#include "LogicGame\Project1\cTower.h"
#include "LogicGame\Project1\cPlayer.h"

class UIManager {
private:
    TileMap map1, map2, map3, map4;
    HUDManager hud;
    TowerSelector selector;
    TowerGhost ghost;
    cPlayer money;
    //Liên quan đến Tower
    std::vector<std::unique_ptr<cTower>> towers; //vector lưu các trụ đặt để vẽ ra mh
    sf::IntRect selectedRect; // vị trí cắt tile vẽ trụ

    sf::Font font;
    sf::Texture towerTex;
    sf::Texture towerBox;
public:
    void init(); // load everything
    void handleClick(sf::Vector2f mouse, sf::RenderWindow&);
    void update(sf::RenderWindow&, float deltaTime);
    void draw(string map, sf::RenderWindow& window);
    sf::Vector2f getMousePos(sf::RenderWindow&);
    std::vector<std::unique_ptr<cTower>>& getTowers();
    // Game data interface
};

