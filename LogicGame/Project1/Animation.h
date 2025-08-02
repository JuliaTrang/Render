#pragma once
#include <SFML/Graphics.hpp>

class Animation {
private:
    sf::Texture texture;
    sf::Sprite sprite;

    int frameWidth;
    int frameHeight;
    int currentFrame;
    int totalFrames;
    float timer;
    float duration;
    int direction; //(0: lên, 1: xuống, 2: phải)

public:
    Animation();
    bool load(std::string filePath, int totalX, int totalY, float dur, int direction = 0);
    void update(float deltaTime);
    void setPosition(sf::Vector2f pos);
    void setDirection(int dir);
    void setScale(float);
    void draw(sf::RenderWindow& window) const;
    void setTexture(const sf::Texture& tex);
    const sf::Texture& getTexture() const { return texture; }
    void setRotation(float angle);
    void setColor(const sf::Color& color);
};

