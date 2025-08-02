#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Scene.h"
#include "winScreen.h"
#include "loseScreen.h"
#include "../../../UIManager.h"
#include "../../../LogicGame/Project1/cTile.h"
#include "../../../LogicGame/Project1/cBullet.h"
#include "../../../LogicGame/Project1/cEnemy.h"
#include "../../../LogicGame/Project1/cTower.h"
#include "../../../LogicGame/Project1/cWave.h"
#include "../../../LogicGame/Project1/cPlayer.h"
#include "../../../LogicGame/Project1/cGame.h"
#include "../../../LogicGame/Project1/cResource.h"

extern bool gameLost;

class GameScene : public Scene {
private:
    std::string currentMapName;
    bool done = false;
    int nextState = 0;

    UIManager UI;
    cPlayer player;
    cGame game;
    winScreen win;
    loseScreen lose;
    std::vector<cTile> path;

    bool isMouseReleased = true;
    bool isWinOpen = false;
    bool isLoseOpen = false;

public:
    GameScene(const std::string& mapName, Difficulty diff);
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    void update(sf::RenderWindow& window, float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    bool isDone() const override { return done; }
    int getNextState() const override { return nextState; }
};

Difficulty getDifficultyForMap(const std::string& map);