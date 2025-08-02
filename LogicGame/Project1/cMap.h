#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;

class cMap {
private:
    sf::Texture m_tileset;
    vector<sf::Sprite> m_tiles;
    vector<sf::Sprite> m_toppings;
    int m_tileWidth, m_tileHeight;

public:
    bool load(const string& tilesetPath, const string& mapPath, int tileWidth, int tileHeight);
    bool loadTopping(const string& toppingPath);
    void draw(sf::RenderWindow& window);
};
