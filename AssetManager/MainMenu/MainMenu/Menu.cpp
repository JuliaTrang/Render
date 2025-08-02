#include "Menu.h"
#include <iostream>
#include <string>
#include <direct.h>

Menu::Menu() {
    textureBackGround.loadFromFile("asset/mainmenu/MainMenu1.png");
    background.setTexture(textureBackGround);
    background.setScale(0.5f, 0.5f);
    background.setPosition(0, 0);

    textureBtn.loadFromFile("asset/mainmenu/Button.png");

    buttons.emplace_back(textureBtn, sf::IntRect(2 * 48, 0, 48, 16), sf::Vector2f(1, 1), sf::Vector2f(64, 84));  // Play
    buttons.emplace_back(textureBtn, sf::IntRect(4 * 48, 0, 48, 16), sf::Vector2f(1, 1), sf::Vector2f(112, 84)); // Load
    buttons.emplace_back(textureBtn, sf::IntRect(1 * 48, 0, 48, 16), sf::Vector2f(1, 1), sf::Vector2f(160, 84)); // Option
    buttons.emplace_back(textureBtn, sf::IntRect(5 * 48, 0, 48, 16), sf::Vector2f(1, 1), sf::Vector2f(208, 84)); // Quit

    music.openFromFile("asset/music/A-Well-Earned-Celebration_Menu.wav");
    music.setVolume(100);
    music.setLoop(true);
    music.play();
}

void Menu::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    // Nếu đang mở overlay (setting/mapList), chỉ xử lý overlay
    if (isSettingOpen) {
        setting.handleEvent(event, window);
        if (setting.getIsOK()) {
            isSettingOpen = false;
            setting.resetIsOK();
        }
        return;
    }

    if (isMapListOpen) {
        mapList.handleEvent(event, window);
        if (mapList.getIsCancel()) {
            isMapListOpen = false;
            mapList.resetIsCancel();
            done = false;
        }
        return;
    }

    // Xử lý sự kiện chuột menu chính
    if (event.type == sf::Event::MouseButtonReleased) {
        isMouseReleased = true;
    }

    if (event.type == sf::Event::MouseButtonPressed && isMouseReleased) {
        isMouseReleased = false;
        for (int i = 0; i < buttons.size(); ++i) {
            if (buttons[i].isClicked(window, event)) {
                switch (i) {
                case 0: // Play
                    isMapListOpen = true;
                    break;
                case 1: // Load
                    nextState = 7;
                    done = true;
                    break;
                case 2: // Option
                    isSettingOpen = true;
                    break;
                case 3: // Quit
                    nextState = 6;
                    done = true;
                    break;
                }
            }
        }
    }
}

void Menu::update(sf::RenderWindow& window, float deltaTime) {
    // Cập nhật nếu đang ở MapList và chọn xong map
    if (isMapListOpen) {
        if (mapList.isDone()) {
            nextState = mapList.getNextState();
            std::cout << "[Menu] Da chon map → chuyen state: " << nextState << "\n";
            done = true;
            isMapListOpen = false;
        }
        else if (mapList.getIsCancel()) {
            isMapListOpen = false;
            mapList.resetIsCancel();
            done = false;
        }
    }
    // Cập nhật nhạc nền
    if (setting.getMuteBackground()) {
        if (music.getStatus() == sf::Music::Playing)
            music.pause();
    }
    else {
        if (music.getStatus() != sf::Music::Playing)
            music.play();
    }
}

void Menu::render(sf::RenderWindow& window) {
    window.draw(background);
    for (auto& but : buttons)
        but.draw(window);

    if (isSettingOpen) {
        sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        window.draw(overlay);
        setting.render(window);
    }

    if (isMapListOpen) {
        sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        window.draw(overlay);
        mapList.render(window);
    }
}
