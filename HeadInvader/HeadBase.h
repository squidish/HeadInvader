#pragma once
#include <SFML/Graphics.hpp>

const int INVADER_HITPOINTS = 40;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

struct HeadConfig {
    float scale = 0.3f;
    float startY = 80.f;
    float halfWidth = 60.f;
    float dropStep = 20.f;
    float speedIncrement = 10.f;
};

class HeadBase {
public:
    virtual ~HeadBase() = default;

    virtual void move(float dt) = 0;
    virtual void draw(sf::RenderWindow  &window) const = 0;
    virtual bool checkBulletHit(const sf::RectangleShape  &bullet) = 0;
    virtual bool isAlive() const  = 0;
    virtual bool hasReachedBottom(float windowHeight) const = 0;
};
