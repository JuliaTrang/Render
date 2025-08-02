#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "button.h"
#include "Scene.h"
#include <vector>

class Setting : public Scene {
private:
    // UI
    sf::Texture textureBackGround;
    sf::Texture textureBtn;
    sf::Sprite background;
    sf::Font font;
    sf::Text musicAffect, musicBackground, settingLet;
    std::vector<Button> buttons;

    // State
    bool isMutedAffect = false;
    bool isMutedBackground = false;
    bool isOK = false;

public:
    Setting();

    // Toggle state
    void toggleMuteAffect() { isMutedAffect = !isMutedAffect; }
    void toggleMuteBackground() { isMutedBackground = !isMutedBackground; }

    // Getters
    bool getMuteAffect() const { return isMutedAffect; }
    bool getMuteBackground() const { return isMutedBackground; }
    bool getIsOK() const { return isOK; }
    void resetIsOK() { isOK = false; }

    // Scene interface
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    void update(sf::RenderWindow& window, float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    int getNextState() const override { return 0; }
    bool isDone() const override { return false; }
};
