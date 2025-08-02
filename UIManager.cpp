#include "UIManager.h"
#include <iostream>
using namespace std;

void UIManager::init() {
    //Forest
    if (!map1.load("asset\\forest\\tilesetforest.png", "asset\\forest\\forestmatrix.txt", 16, 16)) {
        return; 
    }
    if (!map1.loadTopping("asset\\forest\\forest_topping.txt")) {
        return;
    }
    //River
    if (!map2.load("asset\\river\\tilesetriver.png", "asset\\river\\rivermatrix.txt", 16, 16)) {
        return;
    }
    if (!map2.loadTopping("asset\\river\\river_topping.txt")) {
        return;
    }
    //Winter
    if (!map3.load("asset\\winter\\tilesetwinter.png", "asset\\winter\\wintermatrix.txt", 16, 16)) {
        return;
    }
    if (!map3.loadTopping("asset\\winter\\winter_topping.txt")) {
        return;
    }
    //Demon
    if (!map4.load("asset\\demon\\tilesetdemon1.png", "asset\\demon\\demonmatrix.txt", 16, 16)) {
        return;
    }
    if (!map4.loadTopping("asset\\demon\\demon_topping.txt")) {
        return;
    }
    //HUD Manager
    font.loadFromFile("asset\\front\\SVN-Determination Sans.ttf");
    hud.init(font);
    hud.setValues();

    //Tower Selector
    towerTex.loadFromFile("asset\\tower\\tower.png"); 
    towerBox.loadFromFile("asset\\tower\\cardBox.png");
    selector.init(towerTex, towerBox);

}

sf::Vector2f UIManager::getMousePos(sf::RenderWindow& window) {
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
    return worldPos;
}

void UIManager::update(sf::RenderWindow& window, float deltaTime) {
    for (auto& tower : towers)
        if (tower) tower->update(deltaTime); // truyền deltaTime thật nếu có
    if (ghost.active) {
        sf::Vector2f mousePos = getMousePos(window);
        ghost.updatePosition(mousePos);
    }
}

void UIManager::handleClick(sf::Vector2f worldPos, sf::RenderWindow& window){
    if (ghost.active) {
        sf::Vector2f offset(1.f, 7.f); 
        sf::Vector2f pos = worldPos - offset;
        
            // Tạo trụ mới
            std::unique_ptr<cTower> newTower;

            switch (selectedRect.left / 32) {
            case 2: newTower = std::make_unique<Himmel>(); break;
            case 3: newTower = std::make_unique<Stark>(); break;
            case 0: newTower = std::make_unique<Fern>(); break;
            case 1: newTower = std::make_unique<Frieren>(); break;
            default: break;
            }
        if (newTower && playerMoney >= newTower->getCost()) {
            int cost = newTower->getCost();  
            newTower->setLocation(pos);
            towers.push_back(std::move(newTower));
            playerMoney -= cost;
            hud.setValues();
        }
        ghost.updatePosition(pos);
        ghost.active = false;  
    }
    else {
        int selectedIndex = selector.handleClick(getMousePos(window));
        if (selectedIndex != -1) {
            ghost.active = true;
            selectedRect = { selectedIndex * 32, 0, 32, 32 }; // vùng trích texture
            ghost.setSprite(towerTex, selectedRect);
        }
    }
} 

void UIManager::draw(string map, sf::RenderWindow& window){
    if (map == "forest") map1.draw(window);
    else if (map == "river") map2.draw(window);
    else if (map == "winter") map3.draw(window);
    else if (map == "demon") map4.draw(window);
    for (auto& t : towers)
       if(t) t->draw(window);
    selector.draw(window);
    if (ghost.active)
        ghost.draw(window);
    hud.setValues();
    hud.draw(window);
}

// Game data interface


std::vector<std::unique_ptr<cTower>>& UIManager::getTowers() {
    return towers;
}
