#pragma once
#include "HeadBase.h"
//#include <SFML/Graphics.hpp>
#include <optional>
#include <string>

struct HeadConfig {
    float scale = 0.3f;
    float startY = 80.f;
    float halfWidth = 60.f;
    float dropStep = 20.f;
    float speedIncrement = 10.f;
};

class StandardHead : public HeadBase {
public:
    StandardHead(const std::string& textureFile, float initialSpeed, const HeadConfig& config = {});

    void move(float dt);
    bool checkBulletHit(const sf::RectangleShape& bullet);
    bool isAlive() const;
    bool hasReachedBottom(float windowHeight) const;
    void draw(sf::RenderWindow& window) const;

    float speed;
    int hp;
    bool movingRight;

private:
    sf::Texture texture;
    std::optional<sf::Sprite> sprite;
    HeadConfig config;
};
