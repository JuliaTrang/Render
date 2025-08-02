#include "Animation.h"

Animation::Animation() : frameWidth(32), frameHeight(32), currentFrame(0), totalFrames(1), timer(0.f), duration(0.1f), direction(0) {
	sprite.setOrigin(frameWidth / 2.f, frameHeight / 2.f);
	//sprite.setScale(4.f, 4.f);
}

bool Animation::load(std::string filePath, int totalX, int totalY, float dur, int dir)
{
	if (!texture.loadFromFile(filePath))
		return false;
	if (totalX <= 0 || totalY <= 0)
		return false;
	frameWidth = texture.getSize().x / totalX;
	frameHeight = texture.getSize().y / totalY;
	totalFrames = totalX;
	duration = dur;
	direction = dir;
	currentFrame = 0;
	timer = 0.f;
	sprite.setTexture(texture);
	sprite.setOrigin(frameWidth / 2.f, frameHeight / 2.f);
	sprite.setTextureRect(sf::IntRect(0, direction * frameHeight, frameWidth, frameHeight));
	return true;
}

void Animation::update(float deltaTime)
{
	timer += deltaTime;
	if (timer >= duration)
	{
		timer = 0.f;
		currentFrame = (currentFrame + 1) % totalFrames;
		sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, direction * frameHeight, frameWidth, frameHeight));
	}
}

void Animation::setPosition(sf::Vector2f pos)
{
	sprite.setPosition(pos);
}

void Animation::setDirection(int dir)
{
	if (dir >= 0 && dir <= 2 && dir != direction) {
		direction = dir;
		currentFrame = 0;
		sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, direction * frameHeight, frameWidth, frameHeight));
	}
}

void Animation::setScale(float scale)
{
	sprite.setScale(scale, scale);
}

void Animation::draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
}

void Animation::setTexture(const sf::Texture& tex) {
	texture = tex;
	sprite.setTexture(texture);
}

void Animation::setRotation(float angle) {
	sprite.setRotation(angle);
}
void Animation::setColor(const sf::Color& color) {
	sprite.setColor(color);
}