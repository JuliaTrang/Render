#include "winScreen.h"
#include <iostream>

winScreen::winScreen() {
    textureBackGround.loadFromFile("asset/mainmenu/notify.png");
    background.setTexture(textureBackGround);
    background.setPosition(90, 45);
    background.setScale(1.f, 1.f);

    texture.loadFromFile("asset/mainmenu/signalButton.png");

    //quit button & home button
    buttons.emplace_back(texture, sf::IntRect(176, 0, 16, 16), sf::Vector2f(0.6f, 0.6f), sf::Vector2f(150, 100));//home
    buttons.emplace_back(texture, sf::IntRect(16, 0, 16, 16), sf::Vector2f(0.6f, 0.6f), sf::Vector2f(165, 100));//quit

    // Font
    font.loadFromFile("asset/front/SVN-Determination Sans.ttf");

    // Text setup
    youWin.setFont(font);
    youWin.setFillColor(sf::Color(78, 190, 22));
    youWin.setCharacterSize(80);
    youWin.setScale(0.3f, 0.3f);
    youWin.setPosition(122, 60);
    youWin.setString("VICTORY");
}

void winScreen::update(sf::RenderWindow& window, float deltaTime) {
    // Không cần logic động trong map list hiện tại
}


void winScreen::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (done) return;

    for (int i = 0; i < buttons.size(); ++i) {
        if (buttons[i].isClicked(window, event)) {
            switch (i) {
            case 0:
                nextState = 0;
                done = true;
                break;
            case 1:
                nextState = 6;
                done = true;
                break;
            }
            break;
        }
    }
}


void winScreen::render(sf::RenderWindow& window) {
    window.draw(background);
    for (auto& btn : buttons) btn.draw(window);
    window.draw(youWin);
}
