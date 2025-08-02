#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TileMap.h"
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

bool TileMap::load(const string& tilesetPath, const string& mapPath, int tileWidth, int tileHeight) {
    m_tileWidth = tileWidth;
    m_tileHeight = tileHeight;

    pauce.loadFromFile("asset/mainmenu/signalButton.png");

    if (!m_tileset.loadFromFile(tilesetPath)) return false;
                                                  
    ifstream file(mapPath);
    string line;

    int row = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        int tile;
        int col = 0;
        while (ss >> tile) {
            int tx = tile % (m_tileset.getSize().x / tileWidth);
            int ty = tile / (m_tileset.getSize().x / tileWidth);

            sf::Sprite sprite;
            sprite.setTexture(m_tileset);
            sprite.setTextureRect({ tx * tileWidth, ty * tileHeight, tileWidth, tileHeight });
            sprite.setPosition(col * tileWidth, row * tileHeight);
            m_tiles.push_back(sprite);
            col++;
        }
        row++;
    }
    return true;
}

bool TileMap::loadTopping(const string& toppingPath) {
    std::ifstream file(toppingPath);
    if (!file.is_open()) return false;

    int x, y, tileX, tileY, width, height;
    while (file >> x >> y >> tileX >> tileY >> width >> height) {
        sf::Sprite sprite;
        sprite.setTexture(m_tileset);
        sprite.setTextureRect({ tileX * m_tileWidth, tileY * m_tileHeight, width, height });
        sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
        m_toppings.push_back(sprite);
    }
    return true;
}

void TileMap::draw(sf::RenderWindow& window) {
    for (auto& tile : m_tiles) {
        window.draw(tile);
    }    
    for (auto& top : m_toppings) {
        window.draw(top);
    }
        
}
