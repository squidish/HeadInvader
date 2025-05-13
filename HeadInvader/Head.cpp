
#include "Head.h"

const int INVADER_HITPOINTS = 20;
const int WINDOW_WIDTH = 800;

Head::Head(const std::string& textureFile, float initialSpeed)
    : speed(initialSpeed), hp(INVADER_HITPOINTS), movingRight(true) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "[ERROR] Could not load head texture: " << textureFile << "\n";
        exit(EXIT_FAILURE);
    }

    // Construct the sprite now that texture is loaded
    sprite.emplace(texture);
    sprite->setScale(sf::Vector2f(0.3f, 0.3f));
    sprite->setPosition(sf::Vector2f(static_cast<float>(WINDOW_WIDTH / 2.f - 60.f), 80.f));
}

void Head::move(float dt) {
    if (!sprite) return;  // Safety check in case sprite wasn't initialized

    float dx = speed * dt * (movingRight ? 1.f : -1.f);
    sprite->move(sf::Vector2f(dx, 0));

    if (sprite->getPosition().x <= 0.f) {
        movingRight = true;
        sprite->move(sf::Vector2f(0.f, 20.f));
        speed += 10.f;
    }

    float width = static_cast<float>(sprite->getTexture().getSize().x) * sprite->getScale().x;
    if (sprite->getPosition().x + width >= WINDOW_WIDTH) {
        movingRight = false;
        sprite->move(sf::Vector2f(0.f, 20.f));
        speed += 10.f;
    }
}

bool Head::checkBulletHit(const sf::RectangleShape& bullet) {
    if (!sprite) return false;

    if (sprite->getGlobalBounds().findIntersection(bullet.getGlobalBounds()).has_value()) {
        hp--;
        return true;
    }
    return false;
}

bool Head::isAlive() const {
    return hp > 0;
}

bool Head::hasReachedBottom(float windowHeight) const {
    if (!sprite) return false;

    float headBottom = sprite->getPosition().y + sprite->getTexture().getSize().y * sprite->getScale().y;
    return headBottom >= windowHeight;
}

void Head::draw(sf::RenderWindow& window) const {
    if (sprite)
        window.draw(*sprite);
}
