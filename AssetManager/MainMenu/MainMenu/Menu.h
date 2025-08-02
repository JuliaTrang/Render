#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "button.h"
#include "Scene.h"
#include "setting.h"
#include "mapList.h"
#include <vector>

class Menu : public Scene {
private:
    // Graphic
    sf::Texture textureBackGround;
    sf::Texture textureBtn;
    sf::Sprite background;
    std::vector<Button> buttons;

    // State flags
    bool done = false;
    bool isSettingOpen = false;
    bool isMapListOpen = false;
    bool isMouseReleased = false;
    int nextState = 0;

    // Music & UI
    sf::Music music;
    Setting setting;
    MapList mapList;

public:
    Menu();
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    void update(sf::RenderWindow& window, float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    bool isDone() const override { return done; }
    int getNextState() const override { return nextState; }
    bool hasChosenMap() const { return mapList.isDone(); }
    std::string getSelectedMap() const { return mapList.getNextMap(); }
};
