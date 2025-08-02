#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "cBullet.h"

class cBullet;
class cEnemy;
class cTower
{
protected:
    float cooldown; // toc do ban
    float cooldownTimer; // dung trong ham shoot()
    float range;
    float fireAnimTimer = 0.f;
    bool isActive;
    int cost;
    std::vector<std::unique_ptr<cBullet>> activeBullets;
    sf::Vector2f location;
    sf::Texture texture;
    sf::Sprite sprite;
    Animation animation;

    // bullet properties
    int damage;
    float speed;
    std::string bulletAnimationPack;
public:
    cTower();
    cTower(float, float, int, const std::string);
    void shoot(std::vector<std::shared_ptr<cEnemy>>&, float);
    sf::Vector2f getLocation() const;
    void setLocation(sf::Vector2f);
    void update(float deltaTime);
    void draw(sf::RenderWindow&);
    void setActive();
    bool getActive() const;
    int getCost();
    bool isInRange(const cEnemy&) const;
};

class Himmel : public cTower
{
public:
    Himmel() : cTower(5.f, 500.f, 40, "LogicGame/Project1/DesignPx/Tower/Himmel.png") {
        damage = 100;
        speed = 8000.f;
        bulletAnimationPack = "LogicGame/Project1/DesignPx/Projectile/Sword.png"; // add name here
        animation.load("LogicGame/Project1/DesignPx/Animation/Himmel.png", 12, 2, 0.1f, 0);
    };
    
};

class Stark : public cTower
{
public:
    Stark() : cTower(0.5f, 500.f, 50, "LogicGame/Project1/DesignPx/Tower/Stark.png") {
        damage = 20;
        speed = 600.f;
        bulletAnimationPack = "LogicGame/Project1/DesignPx/Projectile/Axe.png";
        animation.load("LogicGame/Project1/DesignPx/Animation/Stark.png", 12, 2, 0.1f, 0);
    };
};

class Fern : public cTower
{
public:
    Fern() : cTower(0.5f, 500.f, 70, "LogicGame/Project1/DesignPx/Tower/Fern.png") {
        damage = 25;
        speed = 600.f;
        bulletAnimationPack = "LogicGame/Project1/DesignPx/Projectile/fireball.png";
        animation.load("LogicGame/Project1/DesignPx/Animation/Fern.png", 12, 2, 0.1f, 0);
    };
};

class Frieren : public cTower
{
public:
    Frieren() : cTower(0.5, 500.f, 100, "LogicGame/Project1/DesignPx/Tower/Frieren.png") {
        damage = 25;
        speed = 700.f;
        bulletAnimationPack = "LogicGame/Project1/DesignPx/Projectile/fireball.png";
        animation.load("LogicGame/Project1/DesignPx/Animation/Frieren.png", 12, 2, 0.1f, 0);
    };
};