#ifndef HEAD_HPP
#define HEAD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Head {
public:
    Head(const std::string& textureFile, float initialSpeed);

    void move(float dt);
    bool checkBulletHit(const sf::RectangleShape& bullet);
    bool isAlive() const;
    bool hasReachedBottom(float windowHeight) const;
    void draw(sf::RenderWindow& window) const;

private:
    sf::Texture texture;
    std::optional<sf::Sprite> sprite;
    int hp;
    float speed;
    bool movingRight;
};

#endif // HEAD_HPP
