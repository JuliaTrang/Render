#include "mapList.h"
#include <iostream>

MapList::MapList() {
    textureBackGround.loadFromFile("asset/mainmenu/maplist.png");
    background.setTexture(textureBackGround);
    background.setPosition(70, 55);
    background.setScale(0.3f, 0.3f);

    textureBtn.loadFromFile("asset/mainmenu/Button.png");
    texture.loadFromFile("asset/mainmenu/signalButton.png");

    // Level buttons
    std::vector<sf::Vector2f> positions = {
        {100, 85}, {170, 85}, {100, 110}, {170, 110}
    };
    for (auto& pos : positions)
        buttons.emplace_back(textureBtn, sf::IntRect(0, 0, 48, 16), sf::Vector2f(1.f, 1.f), pos);

    // Cancel button
    buttons.emplace_back(texture, sf::IntRect(16, 0, 16, 16), sf::Vector2f(0.6f, 0.6f), sf::Vector2f(235, 60));

    // Font
    font.loadFromFile("asset/front/SVN-Determination Sans.ttf");

    // Text setup
    map.setFont(font);
    level1.setFont(font); level2.setFont(font);
    level3.setFont(font); level4.setFont(font);

    map.setFillColor(sf::Color(244, 164, 96));
    for (auto* label : { &level1, &level2, &level3, &level4 })
        label->setFillColor(sf::Color::Black);

    map.setCharacterSize(150);
    for (auto* label : { &level1, &level2, &level3, &level4 })
        label->setCharacterSize(60);

    map.setScale(0.1f, 0.1f);
    level1.setScale(0.1f, 0.1f);
    level2.setScale(0.1f, 0.1f);
    level3.setScale(0.1f, 0.1f);
    level4.setScale(0.1f, 0.1f);

    map.setPosition(145, 60);
    level1.setPosition(113.5f, 89.5f);
    level2.setPosition(183.5f, 89.5f);
    level3.setPosition(113.5f, 114.5f);
    level4.setPosition(183.5f, 114.5f);

    map.setString("MAP");
    level1.setString("Level 1");
    level2.setString("Level 2");
    level3.setString("Level 3");
    level4.setString("Level 4");
}

void MapList::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (done) return;

    for (int i = 0; i < buttons.size(); ++i) {
        if (buttons[i].isClicked(window, event)) {
            isCancel = (i == 4);
            switch (i) {
            case 0: 
                nextMap = "forest"; 
                nextState = 8;
                done = true;
                break;
            case 1: 
                nextMap = "river";
                nextState = 8;
                done = true;
                break;
            case 2: 
                nextMap = "winter"; 
                nextState = 8;
                done = true;
                break;
            case 3: 
                nextMap = "demon"; 
                nextState = 8;
                done = true;
                break;
            case 4: break; // cancel
            }
            break;
        }
    }
}

void MapList::update(sf::RenderWindow& window, float deltaTime) {
    // Không cần logic động trong map list hiện tại
}

void MapList::render(sf::RenderWindow& window) {
    window.draw(background);
    for (auto& btn : buttons) btn.draw(window);
    window.draw(map);
    window.draw(level1);
    window.draw(level2);
    window.draw(level3);
    window.draw(level4);
}
