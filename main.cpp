#include <SFML/Graphics.hpp>
#include "UIManager.h"
#include "AssetManager/MainMenu/MainMenu/Menu.h"
#include "AssetManager/MainMenu/MainMenu/Scene.h"
#include "AssetManager/MainMenu/MainMenu/mapList.h"
#include "AssetManager/MainMenu/MainMenu/GameScene.h"
#include "AssetManager/MainMenu/MainMenu/Setting.h"

enum GameStates {
    MainMenu = 0,
    setting = 1,
    mapWindow = 2,
    PauseMenu = 3,
    winScreen = 4,
    loseScreen = 5,
    exitGame = 6,
    load = 7,
    inGame = 8
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Tower Defense", sf::Style::Default);
    sf::View view;
    view.setSize(320.f, 180.f);
    view.setCenter(160.f, 90.f);
    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    window.setView(view);

    std::string lastMapName;
    Difficulty lastDifficulty;

    srand(static_cast<unsigned>(time(0)));
    sf::Clock clock;
    Scene* currentScene = new Menu();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
            currentScene->handleEvent(event, window);
        }

        float deltaTime = clock.restart().asSeconds();
        currentScene->update(window, deltaTime);
        // Hiển thị
        window.clear();
        currentScene->render(window);
        window.display();

        // Chuyển scene nếu xong
        if (currentScene->isDone()) {
            int nextState = currentScene->getNextState();
            if (auto* menu = dynamic_cast<Menu*>(currentScene)) {
                if (menu->hasChosenMap()) {
                    std::string map = menu->getSelectedMap();
                    lastMapName = map;
                    lastDifficulty = getDifficultyForMap(map);
                    std::cout << "[Main] Chuyen sang GameScene voi map: " << map << std::endl;
                    delete currentScene;
                    currentScene = new GameScene(map, lastDifficulty);
                    continue;
                }
            }

            delete currentScene;

            switch (nextState) {
            case mapWindow:
                currentScene = new MapList();
                break;
            case setting:
                currentScene = new Setting();
                break;
            case MainMenu:
                currentScene = new Menu();
                break;
            case loseScreen:
                currentScene = new GameScene(lastMapName, lastDifficulty);
                break;
            case exitGame:
                window.close();
                return 0;
            default:
                currentScene = new Menu();
                break;
            }
        }
    }

    delete currentScene;
    return 0;
}
