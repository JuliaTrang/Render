#include "cPlayer.h"
#include "cResource.h"
#include <iostream>

int playerMoney = 100;

using namespace std;

void cPlayer::display(sf::RenderWindow& window) {
	sf::Font font;
	if (!font.loadFromFile("asset\\front\\SVN-Determination Sans.ttf"))
	{
		std::cout << "Error\n";
		return;
	}
	sf::Text text;
	text.setString(std::to_string(playerMoney));
	text.setFont(font);
	text.setCharacterSize(80);
	text.setScale(0.1f, 0.1f);
	text.setFillColor(sf::Color::Black);
	text.setPosition(38, 27);
	window.draw(text);
}

