#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "button.h"
#include "Scene.h"
#include <vector>
#include <string>

class loseScreen : public Scene {
private:
    // Graphics
    sf::Texture textureBackGround;
    sf::Texture texture;
    sf::Sprite background;
    sf::Font font;
    sf::Text youWin;
    std::vector<Button> buttons;

    // State
    bool done = false;
    bool isCancel = false;
    int nextState = 0;

public:
    loseScreen();

    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    void update(sf::RenderWindow& window, float deltaTime) override;
    void render(sf::RenderWindow& window) override;

    bool isDone() const override { return done; }
    int getNextState() const override { return nextState; }
    bool getIsCancel() const { return isCancel; }
    void resetIsCancel() { isCancel = false; }
};


