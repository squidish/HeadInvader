#pragma once
#include "HeadBase.h"
//#include <SFML/Graphics.hpp>
#include <optional>
#include <string>


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
