#include "setting.h"
#include <iostream>

Setting::Setting() {
    textureBackGround.loadFromFile("asset/mainmenu/setting.png");
    background.setTexture(textureBackGround);
    background.setPosition(90, 32);
    background.setScale(3.f, 3.f);

    textureBtn.loadFromFile("asset/mainmenu/signalButton.png");

    // Button layout: affect on/off, bg on/off, ok
    buttons.emplace_back(textureBtn, sf::IntRect(4 * 16, 0, 16, 16), sf::Vector2f(0.6f, 0.6f), sf::Vector2f(176, 68)); // Affect ON
    buttons.emplace_back(textureBtn, sf::IntRect(5 * 16, 0, 16, 16), sf::Vector2f(0.6f, 0.6f), sf::Vector2f(189, 68)); // Affect OFF
    buttons.emplace_back(textureBtn, sf::IntRect(8 * 16, 0, 16, 16), sf::Vector2f(0.6f, 0.6f), sf::Vector2f(176, 85)); // BG ON
    buttons.emplace_back(textureBtn, sf::IntRect(9 * 16, 0, 16, 16), sf::Vector2f(0.6f, 0.6f), sf::Vector2f(189, 85)); // BG OFF
    buttons.emplace_back(textureBtn, sf::IntRect(2 * 16, 0, 16, 16), sf::Vector2f(0.6f, 0.6f), sf::Vector2f(160, 102)); // OK

    font.loadFromFile("asset/front/SVN-Determination Sans.ttf");

    musicAffect.setFont(font);
    musicBackground.setFont(font);
    settingLet.setFont(font);

    for (auto* text : { &musicAffect, &musicBackground, &settingLet }) {
        text->setFillColor(sf::Color::Black);
    }

    musicAffect.setCharacterSize(60);
    musicBackground.setCharacterSize(60);
    settingLet.setCharacterSize(80);

    musicAffect.setScale(0.1f, 0.1f);
    musicBackground.setScale(0.1f, 0.1f);
    settingLet.setScale(0.1f, 0.1f);

    musicAffect.setPosition(120, 68);
    musicBackground.setPosition(120, 85);
    settingLet.setPosition(150, 50);

    musicAffect.setString("Music Effect");
    musicBackground.setString("Music Background");
    settingLet.setString("SETTING");
}

void Setting::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    for (int i = 0; i < buttons.size(); ++i) {
        if (buttons[i].isClicked(window, event)) {
            switch (i) {
            case 0: isMutedAffect = false; break;
            case 1: isMutedAffect = true; break;
            case 2: isMutedBackground = false; break;
            case 3: isMutedBackground = true; break;
            case 4: isOK = true; break;
            }
        }
    }
}

void Setting::update(sf::RenderWindow& window, float deltaTime) {
    // Không cần update nội bộ ở đây trong phiên bản này
}

void Setting::render(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(musicAffect);
    window.draw(musicBackground);
    window.draw(settingLet);

    for (auto& but : buttons)
        but.draw(window);
}
