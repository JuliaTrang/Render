#include <SFML/Graphics.hpp>
#include "button.h"
#include <iostream>

Button::Button(sf::Texture& texture, const sf::IntRect& rectangle, const sf::Vector2f& factor, sf::Vector2f position) {
    button.setTexture(texture);
    button.setTextureRect(rectangle);
    button.setPosition(position);
    button.setScale(factor);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(button);
}

bool Button::isMouseOver(sf::RenderWindow& window) {
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
    return button.getGlobalBounds().contains(worldPos);
}


bool Button::isClicked(sf::RenderWindow& window, sf::Event& event) {
    return event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left &&
        isMouseOver(window);
}
