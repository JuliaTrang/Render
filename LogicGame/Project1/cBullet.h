#pragma once
#include <memory>
#include "SFML/Graphics.hpp"
#include "Animation.h"
class cEnemy;

class cBullet
{
private:
    int damage;
    sf::Vector2f position;
    std::weak_ptr<cEnemy> target;
    bool isActive;
    Animation animation;
    //Animation effect;
public:
    cBullet(const cBullet&) = delete;
    cBullet(sf::Vector2f, std::shared_ptr<cEnemy>, int, std::string);
    cBullet& operator=(const cBullet&) = delete;
    cBullet(cBullet&&) = default;
    cBullet& operator=(cBullet&&) = default;
    int getDamage() const;
    bool active() const;
    void move(float, float);
    void draw(sf::RenderWindow&);
};

