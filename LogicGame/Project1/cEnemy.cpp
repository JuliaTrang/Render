#include "cEnemy.h"
#include "cBullet.h"
#include "cPlayer.h"
#include <fstream>
#include <vector>
#include <queue>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 12;
const int MAP_SCALE = 1;

cEnemy::cEnemy() : speed(20), health(100), maxHealth(100), isAlive(true), pathIndex(0), position(0.f, 0.f), reward(15) {
	animation.load("LogicGame/Project1/DesignPx/Animation/Lesser_Demon/type1.png", 7, 3, 0.1f, 0);
}

cEnemy::cEnemy(float spd, int hp, string mapPath, int gold, string animationPath)
	: mapName(mapPath), speed(spd), health(hp), maxHealth(hp), reward(gold), pathIndex(0), position(0.f, 0.f), isAlive(true)
{
	animation.load(animationPath, 7, 3, 0.1f, 0);
}

cEnemy::cEnemy(std::vector<cTile>path, sf::Vector2f startPos) : speed(100), health(100), maxHealth(100),
isAlive(true), path(path), pathIndex(1), position(startPos), reward(15) {
	animation.load("LogicGame/Project1/DesignPx/Animation/Lesser_Demon/type1.png", 7, 3, 0.1f, 0);
}
sf::Vector2f cEnemy::getPosition() const
{
	return position; 
}

void cEnemy::setHealth(int health)
{
	this->health = health;
}

void cEnemy::initializePostion()
{
	position.x = path[0].getX() * cTile::SIZE * 1.f;
	position.y = path[0].getY() * cTile::SIZE * 1.f;
}

void cEnemy::move(float deltaTime)
{
	if (pathIndex >= path.size() || !isAlive) return;
	if (isFlashing) {
		damageFlashTimer -= deltaTime;
		if (damageFlashTimer <= 0.f) {
			isFlashing = false;
			animation.setColor(sf::Color::White);
		}
	}
	sf::Vector2f targetPos = { coordToPixel(path[pathIndex], 1.f) };
	sf::Vector2f toTarget = targetPos - position;
	float distance = std::sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y);

	if (distance < 1.0f)
	{
		position = targetPos;
		pathIndex += 1;
		if (pathIndex >= path.size()) {
			isAlive = false;
			extern bool gameLost;
			gameLost = true;
			return;
		}
	}
	else
	{
		sf::Vector2f direction = toTarget / distance;
		position += direction * speed * deltaTime;
		if (abs(direction.x) > abs(direction.y)) animation.setDirection(0); // phải
		else if (direction.y > 0) animation.setDirection(1); // xuống
		else animation.setDirection(2); // lên
		animation.setPosition(position);
		animation.update(deltaTime);
	}
}
vector<vector<int>> loadFromFile(string filename) {

	vector<vector<int>> map(MAP_HEIGHT, vector<int>(MAP_WIDTH));
	std::ifstream file(filename);
	if (!file.is_open()) return {};
	string line;
	int row = 0;
	while (std::getline(file, line) && row < MAP_HEIGHT) {
		std::stringstream ss(line);
		for (int col = 0; col < MAP_WIDTH; ++col) {
			ss >> map[row][col];
		}
		++row;
	}

	return map;
}

void cEnemy::findPath(int startX, int startY, int endX, int endY, string fileName) {
	vector<vector<bool>> visited(MAP_HEIGHT, vector<bool>(MAP_WIDTH, false));
	vector<vector<cTile>> parent(MAP_HEIGHT, vector<cTile>(MAP_WIDTH));
	queue<cTile> q;
	vector<vector<int>> map = loadFromFile(fileName);

	if (map.empty() || map[0].empty()) {
		std::cerr << "Error: map load failed or empty from file: " << fileName << std::endl;
		return;
	}

	if (startY >= MAP_HEIGHT || startX >= MAP_WIDTH || endY >= MAP_HEIGHT || endX >= MAP_WIDTH) {
		std::cerr << "Error: Start/End point out of map bounds!\n";
		std::cerr << "startX=" << startX << ", startY=" << startY << ", endX=" << endX << ", endY=" << endY << "\n";
		return;
	}

	q.push(cTile(startX, startY));
	visited[startY][startX] = true;

	int dx[] = { 1, -1, 0, 0 };
	int dy[] = { 0, 0, 1, -1 };

	bool foundPath = false;

	while (!q.empty()) {
		cTile current = q.front(); q.pop();
		int cx = current.getX(), cy = current.getY();

		if (cx == endX && cy == endY) {
			foundPath = true;
			break;
		}

		for (int i = 0; i < 4; ++i) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (nx >= 0 && nx < MAP_WIDTH && ny >= 0 && ny < MAP_HEIGHT &&
				!visited[ny][nx] && map[ny][nx] == 1) {
				visited[ny][nx] = true;
				parent[ny][nx] = current;
				q.push(cTile(nx, ny));
			}
		}
	}

	if (!foundPath) {
		std::cerr << "Error: No path found from (" << startX << ", " << startY << ") to (" << endX << ", " << endY << ") in " << fileName << "\n";
		return;
	}

	// reconstruct path
	this->path.clear();
	cTile cur(endX, endY);
	while (!(cur.getX() == startX && cur.getY() == startY)) {
		this->path.push_back(cur);
		cur = parent[cur.getY()][cur.getX()];
	}
	this->path.push_back(cTile(startX, startY));
	std::reverse(this->path.begin(), this->path.end());
	this->pathIndex = 1;
}


void cEnemy::takeDamage(const cBullet& bullet)
{
	if (!isAlive) return;
	int newHealth = health - bullet.getDamage();
	if (newHealth <= 0)
	{
		health = 0;
		isAlive = false;
		playerMoney += reward;
	}
	else
	{
		setHealth(newHealth);
		isFlashing = true;
		damageFlashTimer = 0.2f;
		animation.setColor(sf::Color::Red);
	}
}

void cEnemy::draw(sf::RenderWindow& window)
{
	if (!isAlive) return;
	animation.draw(window);

	// === VẼ THANH MÁU ===
	float maxWidth = 25.f;
	float height = 2.f;
	float offsetY = -20.f;

	float hpPercent = static_cast<float>(health) / maxHealth;
	sf::RectangleShape hpBack(sf::Vector2f(maxWidth, height));
	hpBack.setFillColor(sf::Color(50, 50, 50)); // màu nền
	hpBack.setPosition(position.x - maxWidth / 2.f, position.y + offsetY);

	sf::RectangleShape hpBar(sf::Vector2f(maxWidth * hpPercent, height));
	hpBar.setFillColor(sf::Color::Green); // màu máu
	hpBar.setPosition(position.x - maxWidth / 2.f, position.y + offsetY);

	window.draw(hpBack);
	window.draw(hpBar);
}
void cEnemy::setTexture(const sf::Texture& tex)
{
	animation.setTexture(tex);
}