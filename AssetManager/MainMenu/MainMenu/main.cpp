#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"
#include "Scene.h"

enum GameStates {
    MainMenu = 0,
    setting = 1,
    game = 2,
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

    GameStates state = MainMenu;
    Scene* currentScene = new Menu(); // use your Menu class


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Pass event to current scene
            currentScene->handleEvent(event, window);
        }

        //currentScene->update(); // You can leave empty if not needed

        window.clear();
        currentScene->render(window);
        window.display();

        // If the menu is finished (user clicked something)
        if (currentScene->isDone()) {
            int next = dynamic_cast<Menu*>(currentScene)->getNextState(); // safely get the next state
            delete currentScene;

            switch (next) {
            case setting:
                currentScene = new Setting();  // ✅ nhớ là phải tạo Setting kế thừa Scene
                break;
            case MainMenu:
                currentScene = new Menu();
                break;
            case exitGame:
                window.close();
                break;
            default:
                currentScene = new Menu();
                break;
            }
        }
    }   
    return 0;
}
