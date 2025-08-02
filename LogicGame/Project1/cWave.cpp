#include "cWave.h"
#include "cResource.h"
#include "cEnemy.h"
#include "cTile.h"
#include <algorithm>
#include <cmath>

    cWave::cWave(vector<cTile> path, float interval, int amount) : path(std::move(path)), spawnTimer(0.f), 
    spawnInterval(interval), amount(amount), spawned(0) {}

    bool cWave::isFinished() const
    {
       /* for (int i = 0; i < enemies.size(); i++)
        {
            sf::Vector2f endPos = coordToPixel(sauce.map1);
            if (enemies[i]->getPosition() == endPos) return true;
        }*/

        return spawned >= amount && enemies.empty();
    }

//     cWave::cWave(std::vector<cTile> path, float interval, int amount, std::function<std::unique_ptr<cEnemy>()> factory)
//         : path(std::move(path)), spawnTimer(0.f), spawnInterval(interval), amount(amount), spawned(0), enemyFactory(factory)
//     {}

    cResource texture;
    void cWave::update(float deltaTime)
    {
        if (isFinished()) return;
        spawnTimer += deltaTime;
        if (spawned < amount && spawnTimer >= spawnInterval) {
            auto enemy = enemyFactory();
            enemy->initializePostion();
            enemies.push_back(enemy);
            spawned++;
            spawnTimer = 0.f;
        }
        for (auto& enemy : enemies)
            if (enemy && enemy->alive())
                enemy->move(deltaTime);
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
            [](const std::shared_ptr<cEnemy>& e) {
                return !e || !e->alive();
            }), enemies.end());
    }

    void cWave::draw(sf::RenderWindow& window)
    {
        for (auto& enemy : enemies)
            if (enemy) enemy->draw(window);
    }

    std::vector<shared_ptr<cEnemy>>& cWave::getEnemies() {
        return enemies;
    }

     void cWave::addMonster(shared_ptr<cEnemy> enemy)
     {
         enemies.push_back(std::move(enemy));
         amount++;
     }

     cWave::cWave(std::vector<cTile> path, float interval, int amount, std::function<std::shared_ptr<cEnemy>()> factory)
         : path(std::move(path)), spawnTimer(0.f), spawnInterval(interval), amount(amount), spawned(0), enemyFactory(factory) {
     }