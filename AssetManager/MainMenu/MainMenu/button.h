#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Button {
private:
	sf::Sprite button;
public:
	Button(sf::Texture&, const sf::IntRect&, const sf::Vector2f&, sf::Vector2f position);
	void draw(sf::RenderWindow&);
	bool isMouseOver(sf::RenderWindow& window);
	bool isClicked(sf::RenderWindow& window, sf::Event& event);
};
