#include "cGame.h"

cGame::cGame(float waveInterval, const std::vector<cTile>& path)
    : currentWaveIndex(0), waveInterval(waveInterval), gameFinished(false), path(path), timer(0.f)
{
}

cGame::cGame(Difficulty diff, const std::string& mapName)
 : currentWaveIndex(0), waveInterval(1.5f), gameFinished(false), timer(0.f)
{
    cEnemy enemy;

    int enemyCount = 0;
    float spawnSpeed = 2.f;

    switch (diff) {
    case Easy:
        enemyCount = 5;
        spawnSpeed = 2.5f;
        break;
    case Medium:
        enemyCount = 10;
        spawnSpeed = 2.f;
        break;
    case Hard:
        enemyCount = 20;
        spawnSpeed = 1.5f;
        break;
    case Asia:
        enemyCount = 30;
        spawnSpeed = 1.f;
        break;
    }

        addWave([mapName]() {
            return std::make_shared<Draht>(mapName);
            }, spawnSpeed, enemyCount);

        addWave([mapName]() {
            return std::make_shared<Linie>(mapName);
            }, spawnSpeed, enemyCount);

        addWave([mapName]() {
            return std::make_shared<Lugner>(mapName);
            }, spawnSpeed, enemyCount);

        // Nếu muốn thêm boss cuối
        addWave([mapName]() {
            return std::make_shared<Aura>(mapName);
            }, spawnSpeed + 1.f, 1);
}

void cGame::update(float deltaTime)
{
    if (gameFinished || currentWaveIndex >= waves.size()) {
        gameFinished = true;
        return;
    }

    auto& currentWave = waves[currentWaveIndex];
    currentWave->update(deltaTime);
    timer += deltaTime;
    if (currentWave->isFinished() || timer >= 80.f) {
        currentWaveIndex++;
        timer = 0.f;
        if (currentWaveIndex >= waves.size()) {
            gameFinished = true;
        }
    }
}


void cGame::draw(sf::RenderWindow& window)
{
    if (gameFinished || currentWaveIndex >= waves.size()) return;
    waves[currentWaveIndex]->draw(window);
}

bool cGame::isGameFinished() const
{
    return gameFinished;
}

std::vector<std::shared_ptr<cEnemy>>& cGame::getCurrentEnemies()
{
    if (gameFinished || currentWaveIndex >= waves.size()) {
        static std::vector<std::shared_ptr<cEnemy>> empty;
        return empty;
    }
    return waves[currentWaveIndex]->getEnemies();
}

void cGame::addWave(std::function<std::shared_ptr<cEnemy>()> factory, float spawnInterval, int amount)
{
    waves.push_back(std::make_unique<cWave>(path, spawnInterval, amount, factory));
}

