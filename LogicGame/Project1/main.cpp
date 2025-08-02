#include "cTile.h"
#include "cBullet.h"
#include "cEnemy.h"
#include "cMap.h"
#include "cTower.h"
#include <iostream>
#include "cWave.h"
#include "cPlayer.h"
#include "cGame.h"
#include "cResource.h"

int playerMoney = 100;
int tileWidth = 16;
int tileHeight = 16;
int cols = 20;  
int rows = 12;

int mapWidth = tileWidth * cols;
int mapHeight = tileHeight * rows;

cEnemy type1(2.f, 100, "fileName.txt", 15, "DesignPx/Animation/type1.png");
cEnemy type2(2.f, 100, "fileName.txt", 15, "DesignPx/Animation/type2.png");
cEnemy type3(2.f, 100, "fileName.txt", 15, "DesignPx/Animation/type3.png");
cEnemy type4(2.f, 100, "fileName.txt", 15, "DesignPx/Animation/type4.png");

int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "TowerDef.exe", sf::Style::Fullscreen);

   // sf::View view(sf::FloatRect(0, 0, static_cast<float>(mapWidth), static_cast<float>(mapHeight)));
    //view.setCenter(mapWidth / 2.f, mapHeight / 2.f);
    //window.setView(view);

    std::vector<cTile> path;
    for (int i = 0; i < 80; i++)
    {
        cTile tile(i, 22, 0);
        path.push_back(tile);
    }

    sf::Clock clock;

    Himmel tower;
    Frieren tower2;
    cEnemy enemy(path, coordToPixel(path[0]));
    enemy.findPath(4, 0, 19, 8, "fileName.txt");
    enemy.initializePostion();
    //cWave wave(enemy.getPath(), 2.f, 10);
    cGame game(Difficulty::Easy);
    cPlayer money;

    cMap map;
    sf::Texture tileset;
    map.load("DesignPx/tilesetwinter.png", "wintermatrix.txt", 16, 16);
    map.loadTopping("winter_top.txt");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }
        float deltaTime = clock.restart().asSeconds();

        window.clear();
        map.draw(window);

        //auto& enemies = wave.getEnemies();
        auto& enemies = game.getCurrentEnemies();
        game.update(deltaTime);
        tower2.update(deltaTime);
        tower2.setLocation({ 200.f, 500.f });
        tower2.draw(window);
        tower2.shoot(enemies, deltaTime);

        tower.update(deltaTime);
        tower.setLocation({ 1000.f, 200.f });
        tower.draw(window);
        tower.shoot(enemies, deltaTime);
        

        //wave.update(deltaTime);
        //wave.draw(window);
        
        game.draw(window);

        money.display(window);

        window.display();
    }

    return 0;
}