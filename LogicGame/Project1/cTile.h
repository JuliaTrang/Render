#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class cTile
{
private:
    int x, y, type;
public:
    static const int SIZE = 16; // 1 tile = 16 pixels
    cTile();
    cTile(int, int, int);
    cTile(int, int);
    int getX() const;
    int getY() const;
    int getType() const;
    void setType(int);
    void drawTile(sf::RenderWindow&, const std::vector<sf::Texture>&) const;
};

sf::Vector2f coordToPixel(const cTile&, float scale = 1.f);

