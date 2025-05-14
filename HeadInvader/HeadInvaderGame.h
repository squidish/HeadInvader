// HeadInvader.h : Include file for standard system include files,
// or project specific include files.

#ifndef HEADINVADERGAME_HPP
#define HEADINVADERGAME_HPP

#include <SFML/Graphics.hpp>
#include <optional>
#include <string>
#include "Head.h"
#include "MusicManager.h"

class HeadInvaderGame {
public:
    HeadInvaderGame();
    void run();

private:
    void setupTexts();
    void selectHead();
    void setupGame();
    void handleEvents();
    void update(float dt);
    void render();

    sf::RenderWindow window;
    sf::RectangleShape player;
    sf::RectangleShape bullet;
    bool bulletActive;
    sf::Vector2f bulletVelocity;

    std::string selectedHeadTextureFile;
    std::optional<Head> head;

    float playerSpeed;
    bool gameOver;
    bool win;

    sf::Font font;
    std::optional<sf::Text> menuText;
    std::optional<sf::Text> winText;
    std::optional<sf::Text> loseText;
    std::optional<sf::Text> restartText;

    MusicManager music;
};

#endif // HEADINVADERGAME_HPP
