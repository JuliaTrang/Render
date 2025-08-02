#include "cBullet.h"
#include "cEnemy.h"
#include <cmath>

// official
cBullet::cBullet(sf::Vector2f startPos, std::shared_ptr<cEnemy> target, int damage, std::string animationPack) : position(startPos), target(target), damage(damage), isActive(true)
{
	animation.load(animationPack, 13, 1, 0.1f, 0);
}
//cBullet::cBullet(sf::Vector2f startPos, std::shared_ptr<cEnemy> target) : position(startPos), target(target), damage(10), isActive(true), speed(800.0f)
//{
//	animation.loadProjectile("DesignPx/Projectile/Axe.png", 13, 0.03f);
//	//effect.loadProjectile("DesignPx / Projectile / Axe.png", 13, 0.03f);
//}



int cBullet::getDamage() const { return damage; }
bool cBullet::active() const { return isActive; }

void cBullet::move(float deltaTime, float speed)
{
	auto targetLocked = target.lock();
	if (!targetLocked || !targetLocked->alive())
	{
		isActive = false;
		return;
	}
	sf::Vector2f currentPos = targetLocked->getPosition();
	sf::Vector2f toTarget = currentPos - position;
	float distance = std::sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y);
	if (distance < 1.0f)
	{
		targetLocked->takeDamage(*this);
		isActive = false;
		return;
	}
	else
	{
		sf::Vector2f direction = toTarget / distance;
		float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159265f - 90.f;
		animation.setRotation(angle);
		position += direction * speed * deltaTime;
		animation.setPosition(position); 
		animation.update(deltaTime);
	}
}

void cBullet::draw(sf::RenderWindow& window) {
	animation.setPosition(position);
	animation.draw(window);
}