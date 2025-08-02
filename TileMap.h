#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include "AssetManager/MainMenu/MainMenu/button.h"
using namespace std;

class TileMap {
private:
    sf::Texture m_tileset, pauce;
    vector<sf::Sprite> m_tiles;
    vector<sf::Sprite> m_toppings;
    int m_tileWidth, m_tileHeight;
public:
    bool load(const string& tilesetPath, const string& mapPath, int tileWidth, int tileHeight);
    bool loadTopping(const string& toppingPath);
    void draw(sf::RenderWindow& window);
};

