#include "TowerSelection.h"
#include <iostream>
#include <vector>
using namespace std;

void TowerSelector::init(sf::Texture& texture, sf::Texture& textureBox) {
    for (int i = 0; i < 4; ++i) {
        sf::Sprite icon;
        icon.setTexture(texture); 
        icon.setTextureRect({ i * 32, 0, 32, 32 });
        icon.setScale(0.9f, 0.9f);
        icon.setPosition(190.f + i * 27.f, 148.f); // ngang
        //icon.setPosition(288.f, 64.f + i * 27.f); // doc
        towerIcons.push_back(icon);

        sf::Sprite box;
        box.setTexture(textureBox);
        box.setScale(1.75f, 1.75f);
        box.setColor(sf::Color(250, 250, 250));
        box.setPosition(190.f + i * 27.f, 148.f);
        //box.setPosition(288.f, 64.f + i * 27.f);
        towerBox.push_back(box);
    }
}

int TowerSelector::handleClick(sf::Vector2f mousePos) {
    for (int i = 0; i < towerIcons.size(); ++i) {
        if (towerIcons[i].getGlobalBounds().contains(mousePos))
            return i; // tower index
    }
    return -1;
}

void TowerSelector::draw(sf::RenderWindow& window) {
    for (auto& box : towerBox) window.draw(box);
    for (auto& icon : towerIcons) window.draw(icon);
}
