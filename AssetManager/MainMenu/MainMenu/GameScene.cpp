#include "GameScene.h"
#include <iostream>

bool gameLost = false;

GameScene::GameScene(const std::string& mapName, Difficulty diff)
    : currentMapName(mapName), game(diff, mapName) {

    std::cout << ">>> GameScene created with map: " << mapName << std::endl;
    UI.init();
    for (int i = 0; i < 80; ++i)
        path.emplace_back(i, 22, 0);

}

void GameScene::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (isWinOpen) {
        win.handleEvent(event, window);
        isWinOpen = false;
        return;
    }

    if (isLoseOpen) {
        lose.handleEvent(event, window);
        isLoseOpen = false;
        return;
    }
    if (event.type == sf::Event::Closed) {
        window.close();
        return;
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        done = true;
        nextState = 0;  // back to menu
        return;
    }

    // Xử lý click một lần khi release
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f worldPos = UI.getMousePos(window);
        UI.handleClick(worldPos, window);
    }
}

void GameScene::update(sf::RenderWindow& window, float deltaTime) {
    game.update(deltaTime);
    UI.update(window, deltaTime);

    for (auto& tower : UI.getTowers()) {
        if (tower) {
            auto enemies = game.getCurrentEnemies();
            std::cout << "[DEBUG] Tower shoot: enemy count = " << enemies.size() << std::endl;
            tower->update(deltaTime);
            tower->shoot(game.getCurrentEnemies(), deltaTime);
        }
    }

    if (gameLost) {
        isLoseOpen = true;
        if (lose.isDone()) {
            int loseNext = lose.getNextState();
            done = true;
            gameLost = false; // reset
            if (loseNext == 5) {
                nextState = 5; // replay
            }
            else {
                nextState = 0; // về menu
            }
        }
    }
    else if(game.isGameFinished() && !gameLost) {
        isWinOpen = true;
        if (win.isDone()) {
            done = true;
            gameLost = false; // reset
        }
    }
}

void GameScene::render(sf::RenderWindow& window) {
    for (auto& tower : UI.getTowers()) {
        if (tower)
            tower->draw(window);
    }

    UI.draw(currentMapName, window);
    game.draw(window);
    if (isWinOpen) {
        sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        window.draw(overlay);
        win.render(window);
    }

    if (isLoseOpen) {
        sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        window.draw(overlay);
        lose.render(window);
    }
}

Difficulty getDifficultyForMap(const std::string& map) {
    if (map == "forest") return Difficulty::Easy;
    if (map == "river") return Difficulty::Medium;
    if (map == "winter") return Difficulty::Hard;
    if (map == "demon") return Difficulty::Asia;
    return Difficulty::Easy; // default fallback
}
