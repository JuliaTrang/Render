#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "cTile.h"
#include <string>
#include "cBullet.h"
#include "cPlayer.h"

class cEnemy
{
protected:
    float speed;
    int health;
    int maxHealth;
    bool isAlive;
    std::vector<cTile> path;
    int pathIndex;
    sf::Vector2f position; // position on the screen
    int reward;
    Animation animation;
    float damageFlashTimer = 0.f;
    bool isFlashing = false;
    std::string mapName;

public:
    cEnemy();
    cEnemy(float, int, std::string,int, std::string);
    cEnemy(std::vector<cTile>, sf::Vector2f);
    bool alive() const { return isAlive; }
    sf::Vector2f getPosition() const;
    void setHealth(int);
    void initializePostion();
    void move(float);
    void findPath(int, int, int, int, std::string);
    void takeDamage(const cBullet&);
    void draw(sf::RenderWindow&);
    std::vector<cTile> getPath() { return path; }
    void setTexture(const sf::Texture& tex);
    sf::Texture getTexture() { return animation.getTexture(); }
};
class Draht : public cEnemy {
    
public:
    Draht(const std::string& mapName) : cEnemy(100.f, 100, "asset/" + mapName + "/" + mapName + "path.txt", 15, "LogicGame/Project1/DesignPx/Animation/type1.png") {
        animation.load("LogicGame/Project1/DesignPx/Animation/type1.png", 7, 3, 0.1f, 0);
        int startX, startY, endX, endY;
        if (mapName == "forest") {
            startX = 2; startY = 11; endX = 16; endY = 0;
        }
        else if (mapName == "river") {
            startX = 0; startY = 4; endX = 19; endY = 8;
        }
        else if (mapName == "winter") {
            startX = 4; startY = 0; endX = 19; endY = 8;
        }
        else if (mapName == "demon") {
            std::vector<std::pair<int, int>> startPoints = {
                {0, 3},
                {0, 8}
            };
            std::vector<std::pair<int, int>> endPoints = {
                {19, 8},
                {15, 11}
            };

            // Random 1 trong 2 vị trí start và end
            int startIndex = rand() % startPoints.size();
            int endIndex = rand() % endPoints.size();

            startX = startPoints[startIndex].first;
            startY = startPoints[startIndex].second;
            endX = endPoints[endIndex].first;
            endY = endPoints[endIndex].second;
        }
        this->findPath(startX, startY, endX, endY, "asset/" + mapName + "/" + mapName + "path.txt");
    }
};
class Linie : public cEnemy {
public:
    Linie(const std::string& mapName) : cEnemy(200.f, 80, "asset/" + mapName + "/" + mapName + "path.txt", 15, "LogicGame/Project1/DesignPx/Animation/type2.png") {
        animation.load("LogicGame/Project1/DesignPx/Animation/type2.png", 7, 3, 0.1f, 0);
        int startX, startY, endX, endY;
        if (mapName == "forest") {
            startX = 2; startY = 11; endX = 16; endY = 0;
        }
        else if (mapName == "river") {
            startX = 0; startY = 4; endX = 19; endY = 8;
        }
        else if (mapName == "winter") {
            startX = 4; startY = 0; endX = 19; endY = 8;
        }
        else if (mapName == "demon") {
            std::vector<std::pair<int, int>> startPoints = {
                {0, 3},
                {0, 8}
            };
            std::vector<std::pair<int, int>> endPoints = {
                {19, 8},
                {15, 11}
            };

            // Random 1 trong 2 vị trí start và end
            int startIndex = rand() % startPoints.size();
            int endIndex = rand() % endPoints.size();

            startX = startPoints[startIndex].first;
            startY = startPoints[startIndex].second;
            endX = endPoints[endIndex].first;
            endY = endPoints[endIndex].second;
        }
        this->findPath(startX, startY, endX, endY, "asset/" + mapName + "/" + mapName + "path.txt");
    }
};
class Lugner : public cEnemy {
public:
    Lugner(const std::string& mapName) : cEnemy(60.f, 300, "asset/" + mapName + "/" + mapName + "path.txt", 15, "LogicGame/Project1/DesignPx/Animation/type3.png") {
        animation.load("LogicGame/Project1/DesignPx/Animation/type3.png", 7, 3, 0.1f, 0);
        int startX, startY, endX, endY;
        if (mapName == "forest") {
            startX = 2; startY = 11; endX = 16; endY = 0;
        }
        else if (mapName == "river") {
            startX = 0; startY = 4; endX = 19; endY = 8;
        }
        else if (mapName == "winter") {
            startX = 4; startY = 0; endX = 19; endY = 8;
        }
        else if (mapName == "demon") {
            std::vector<std::pair<int, int>> startPoints = {
                {0, 3},
                {0, 8}
            };
            std::vector<std::pair<int, int>> endPoints = {
                {19, 8},
                {15, 11}
            };

            // Random 1 trong 2 vị trí start và end
            int startIndex = rand() % startPoints.size();
            int endIndex = rand() % endPoints.size();

            startX = startPoints[startIndex].first;
            startY = startPoints[startIndex].second;
            endX = endPoints[endIndex].first;
            endY = endPoints[endIndex].second;
        }
        this->findPath(startX, startY, endX, endY, "asset/" + mapName + "/" + mapName + "path.txt");
    }
};
class Aura : public cEnemy {
public:
    Aura(const std::string& mapName) : cEnemy(60.f, 1000, "asset/" + mapName + "/" + mapName + "path.txt", 15, "LogicGame/Project1/DesignPx/Animation/type4.png") {
        animation.load("LogicGame/Project1/DesignPx/Animation/type4.png", 7, 3, 0.1f, 0);
        int startX, startY, endX, endY;
        if (mapName == "forest") {
            startX = 2; startY = 11; endX = 16; endY = 0;
        }
        else if (mapName == "river") {
            startX = 0; startY = 4; endX = 19; endY = 8;
        }
        else if (mapName == "winter") {
            startX = 4; startY = 0; endX = 19; endY = 8;
        }
        else if (mapName == "demon") {
            std::vector<std::pair<int, int>> startPoints = {
                {0, 3},
                {0, 8}
            };
            std::vector<std::pair<int, int>> endPoints = {
                {19, 8},
                {15, 11}
            };

            // Random 1 trong 2 vị trí start và end
            int startIndex = rand() % startPoints.size();
            int endIndex = rand() % endPoints.size();

            startX = startPoints[startIndex].first;
            startY = startPoints[startIndex].second;
            endX = endPoints[endIndex].first;
            endY = endPoints[endIndex].second;
        }
        this->findPath(startX, startY, endX, endY, "asset/" + mapName + "/" + mapName + "path.txt");
    }
};