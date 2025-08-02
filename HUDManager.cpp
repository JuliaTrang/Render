#include "HUDManager.h"
#include <iostream>

// HUDManager.cpp
void HUDManager::init(sf::Font& font) {
    goldText.setFont(font); moneyText.setFont(font);
    goldText.setFillColor(sf::Color::Black);
    //moneyText.setFillColor(sf::Color::Black);
    goldText.setCharacterSize(80);
    //moneyText.setCharacterSize(80);
    goldText.setScale(0.1f, 0.1f);
    //moneyText.setScale(0.1f, 0.1f);
    goldText.setPosition(18, 8);
    //moneyText.setPosition(18, 27);

    boxTexture.loadFromFile("asset\\mainmenu\\Button.png");
    goldBox.setTexture(boxTexture);
    goldBox.setTextureRect({ 0, 0, 48, 16 });
    goldBox.setScale(1.25f, 1.25f);
    goldBox.setPosition(5, 3);

   /* moneyBox.setTexture(boxTexture);
    moneyBox.setTextureRect({ 0, 0, 48, 16 });
    moneyBox.setScale(1.25f, 1.25f);
    moneyBox.setPosition(5, 22);*/
}

void HUDManager::setValues() {
    goldText.setString("Gold: " + std::to_string(playerMoney));
    //moneyText.setString("Earn: ");
}

void HUDManager::draw(sf::RenderWindow& window) {
    window.draw(goldBox); //window.draw(moneyBox);
    window.draw(goldText); //window.draw(moneyText);
}
