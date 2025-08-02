#pragma once
#include "SFML/Graphics.hpp"
#include "cTile.h"
class cResource
{
public:
	int playerMoney;
	sf::Texture type1;
	sf::Texture type2;
	sf::Texture type3;
	sf::Texture type4;
	cTile map1;
	cResource();
};
extern cResource sauce;

