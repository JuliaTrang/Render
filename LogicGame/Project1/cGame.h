#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <functional>
#include "cWave.h"
#include "cTile.h"
#include "cEnemy.h"
enum Difficulty
{
    Easy,
    Medium,
    Hard,
    Asia
};
class cGame {
private:
    std::vector<std::unique_ptr<cWave>> waves;
    int currentWaveIndex;
    float waveInterval;
    bool gameFinished;
    std::vector<cTile> path;
    float timer;
    void addWave(std::function<std::shared_ptr<cEnemy>()>, float, int);

public:
    cGame(float waveInterval, const std::vector<cTile>& path);
    cGame(Difficulty, const std::string&);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isGameFinished() const;
    
    std::vector<std::shared_ptr<cEnemy>>& getCurrentEnemies();
};
