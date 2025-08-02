#include "cMap.h"
#include <fstream>
#include <sstream>
using namespace std;

bool cMap::load(const string& tilesetPath, const string& mapPath, int tileWidth, int tileHeight) {
    float scale = 6.f;
    m_tileWidth = tileWidth;
    m_tileHeight = tileHeight;

    if (!m_tileset.loadFromFile(tilesetPath)) return false;

    ifstream file(mapPath);
    string line;
    int row = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        int tile, col = 0;
        while (ss >> tile) {
            int tx = tile % (m_tileset.getSize().x / tileWidth);
            int ty = tile / (m_tileset.getSize().x / tileWidth);

            sf::Sprite sprite;
            sprite.setTexture(m_tileset);
            sprite.setTextureRect({ tx * tileWidth, ty * tileHeight, tileWidth, tileHeight });

            sprite.setPosition(col * tileWidth * scale, row * tileHeight * scale);

            sprite.setScale(scale, scale);
            m_tiles.push_back(sprite);
            col++;
        }
        row++;
    }
    return true;
}


bool cMap::loadTopping(const std::string& toppingPath) {
    std::ifstream file(toppingPath);
    if (!file.is_open()) return false;

    float scale = 6.f;
    int x, y, tileX, tileY, width, height;
    while (file >> x >> y >> tileX >> tileY >> width >> height) {
        sf::Sprite sprite;
        sprite.setTexture(m_tileset);
        sprite.setTextureRect({ tileX * m_tileWidth, tileY * m_tileHeight, width, height });

        sprite.setPosition(x * scale, y * scale);  
        sprite.setScale(5.f, 5.f);              
        m_toppings.push_back(sprite);
    }
    return true;
}


void cMap::draw(sf::RenderWindow& window) {
    sf::Transform translate;
    translate.translate(-50.f, 0.f); // Dịch sang trái 100px

    sf::RenderStates states;
    states.transform = translate;

    for (auto& tile : m_tiles)
        window.draw(tile, states); // Áp dụng transform

    for (auto& top : m_toppings)
        window.draw(top, states); // Áp dụng transform
}