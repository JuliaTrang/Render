#include "cTower.h"
#include "cBullet.h"
#include "cEnemy.h"
#include <cmath>

int cTower::getCost() {
    return this->cost;
}

// official
cTower::cTower(float cooldown, float range, int cost, std::string textureName) : cooldown(cooldown), cooldownTimer(0.0f), range(range), location(0.f, 0.f),
isActive(true), cost(cost), damage(1), speed(100.f)
{
    if (!texture.loadFromFile(textureName))
    {
        return;
    }
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 1.f, texture.getSize().y / 1.f);
    sprite.setPosition(location);
    sprite.setScale(1.f, 1.f);
}

void cTower::shoot(std::vector<std::shared_ptr<cEnemy>>& enemies, float deltaTime)
{
    if (!isActive) return;
    cooldownTimer -= deltaTime;

    if (cooldownTimer <= 0)
    {
        for (auto& enemy : enemies)
        {
            if (enemy && enemy->alive() && isInRange(*enemy))
            {
                activeBullets.emplace_back(std::make_unique<cBullet>(location, enemy, damage, bulletAnimationPack));
                cooldownTimer = cooldown;
                fireAnimTimer = cooldown;
                animation.setDirection(1);
                break;
            }
        }
    }

    for (auto& bullet : activeBullets)
    {
        if (bullet) bullet->move(deltaTime, speed);
    }

    activeBullets.erase(std::remove_if(activeBullets.begin(), activeBullets.end(),
        [](const std::unique_ptr<cBullet>& b) { return !b || !b->active(); }),
        activeBullets.end());
}

sf::Vector2f cTower::getLocation() const
{
    return location;
}

void cTower::setLocation(sf::Vector2f position)
{
    if (position.x >= 0.f && position.y >= 0.f)
    {
        location = position;
        sprite.setPosition(location);
        animation.setPosition(location);
    }
}

void cTower::update(float deltaTime)
{
    animation.update(deltaTime);
    if (fireAnimTimer > 0.f) {
        fireAnimTimer -= deltaTime;
        if (fireAnimTimer <= 0.f)
            animation.setDirection(0); 
    }
}

void cTower::draw(sf::RenderWindow& window)
{
    animation.draw(window);
    for (auto& bullet : activeBullets)
    {
        if (bullet && bullet->active()) bullet->draw(window);
    }
}

void cTower::setActive() { isActive = true; }

bool cTower::getActive() const { return isActive; }

bool cTower::isInRange(const cEnemy& enemy) const
{
    if (!enemy.alive()) return false;

    sf::Vector2f enemyPos = enemy.getPosition();
    float dx = enemyPos.x - location.x;
    float dy = enemyPos.y - location.y;
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance <= range;
}

