#include "cTile.h"
#include <SFML/Graphics.hpp> 

cTile::cTile() : x(0), y(0), type(0) {}
cTile::cTile(int x, int y, int t) : x(x), y(y), type(t) {}
cTile::cTile(int x, int y) : x(x), y(y), type(0) {}

int cTile::getX() const { return x; }
int cTile::getY() const { return y; }
int cTile::getType() const { return type; }
void cTile::setType(int t) { type = t; }

void cTile::drawTile(sf::RenderWindow& window, const std::vector<sf::Texture>& texturePack) const {
    if (type < 0 || type >= texturePack.size()) return;
    sf::Sprite sprite;
    sprite.setTexture(texturePack[type]);
    sprite.setPosition(static_cast<float>(x * SIZE), static_cast<float>(y * SIZE));
    window.draw(sprite);
}

sf::Vector2f coordToPixel(const cTile& tile, float scale) {
    return {
        static_cast<float>(tile.getX() * cTile::SIZE * scale),
        static_cast<float>(tile.getY() * cTile::SIZE * scale)
    };
}
