#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <functional>

class cResource;
class cEnemy;
class cTile;

using namespace std;

class cWave {
	std::vector<cTile> path;
	std::vector<shared_ptr<cEnemy>> enemies;
	float spawnTimer;
	float spawnInterval;
	int amount;	//So luong toi da
	int spawned; //So luong da sinh ra
	
	std::function<std::shared_ptr<cEnemy>()> enemyFactory;

public:
	cWave(std::vector<cTile> path, float interval, int amount, std::function<std::shared_ptr<cEnemy>()> factory);
    cWave(std::vector<cTile>, float, int);
//	cWave(std::vector<cTile>, float, int, std::function<std::unique_ptr<cEnemy>()>);
    void update(float deltaTime);
	  void draw(sf::RenderWindow&);
    bool isFinished() const;
	void addMonster(shared_ptr<cEnemy>);
    std::vector<shared_ptr<cEnemy>>& getEnemies();
};

