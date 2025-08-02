#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "button.h"
#include "Scene.h"
#include <vector>
#include <string>

class MapList : public Scene {
private:
    // Graphics
    sf::Texture textureBackGround;
    sf::Texture textureBtn, texture;
    sf::Sprite background;
    sf::Font font;
    sf::Text map, level1, level2, level3, level4;
    std::vector<Button> buttons;

    // State
    bool done = false;
    bool isCancel = false;
    int nextState = 0;
    std::string nextMap;

public:
    MapList();

    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    void update(sf::RenderWindow& window, float deltaTime) override;
    void render(sf::RenderWindow& window) override;

    bool isDone() const override { return done; }
    int getNextState() const override { return nextState; }
    std::string getNextMap() const { return nextMap; }
    bool getIsCancel() const { return isCancel; }
    void resetIsCancel() { isCancel = false; }
};
