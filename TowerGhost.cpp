#include <SFML/Graphics.hpp>
#include "TowerGhost.h" 

void TowerGhost::setSprite(sf::Texture& texture, sf::IntRect rect) {
		ghost.setTexture(texture);
		ghost.setTextureRect(rect);
}
void TowerGhost::updatePosition(sf::Vector2f mousePos) {
	if (active) {
		sf::Vector2f offset(16.f, 25.f);
		sf::Vector2f pos = mousePos - offset;
		ghost.setPosition(pos);
	}
}
void TowerGhost::draw(sf::RenderWindow& window) {
	window.draw(ghost);
}