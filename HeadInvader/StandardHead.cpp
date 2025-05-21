
#include "StandardHead.h"
#include <iostream>



StandardHead::StandardHead(const std::string& textureFile, float initialSpeed, const HeadConfig& cfg)
    : speed(initialSpeed), hp(INVADER_HITPOINTS), movingRight(true), config(cfg) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "[ERROR] Could not load head texture: " << textureFile << "\n";
        exit(EXIT_FAILURE);
    }

    sprite.emplace(texture);
    sprite->setScale(sf::Vector2f(config.scale, config.scale));
    sprite->setOrigin(sf::Vector2f(
        sprite->getTexture().getSize().x / 2.f,
        sprite->getTexture().getSize().y / 2.f)
    );
    sprite->setPosition(sf::Vector2f(
        WINDOW_WIDTH / 2.f,
        config.startY + sprite->getTexture().getSize().y * config.scale / 2.f)
    );
}

void StandardHead::move(float dt) {
    if (!sprite) return;

    float dx = speed * dt * (movingRight ? 1.f : -1.f);
    sprite->move(sf::Vector2f(dx, 0));

    // Flip based on direction
    sprite->setScale(sf::Vector2f(
        movingRight ? std::abs(config.scale) : -std::abs(config.scale),
        config.scale
    ));

    sf::FloatRect bounds = sprite->getGlobalBounds();

    // Hit left edge
    if (bounds.position.x <= 0.f) {
        movingRight = true;
        sprite->move(sf::Vector2f(0.f, config.dropStep));
        speed += config.speedIncrement;
    }

    //Hit right edge
    float width = static_cast<float>(sprite->getTexture().getSize().x) * sprite->getScale().x;
    if (bounds.position.x + bounds.size.x >= WINDOW_WIDTH) {
        movingRight = false;
        sprite->move(sf::Vector2f(0.f, config.dropStep));
        speed += config.speedIncrement;
    }
}

bool StandardHead::checkBulletHit(const sf::RectangleShape& bullet) {
    if (!sprite) return false;

    if (sprite->getGlobalBounds().findIntersection(bullet.getGlobalBounds()).has_value()) {
        hp--;
        return true;
    }
    return false;
}

bool StandardHead::isAlive() const {
    return hp > 0;
}

bool StandardHead::hasReachedBottom(float windowHeight) const {
    if (!sprite) return false;

    float headBottom = sprite->getPosition().y + sprite->getTexture().getSize().y * sprite->getScale().y;
    return headBottom >= windowHeight;
}

void StandardHead::draw(sf::RenderWindow& window) const {
    if (sprite)
        window.draw(*sprite);
}
