#pragma once

#include "HeadBase.h"
#include <SFML/Graphics.hpp>
#include <cstdlib> // rand()
#include <ctime>   // time()
#include<iostream>


class TeleportingHead : public HeadBase {
private:
    sf::Texture texture;
    std::optional<sf::Sprite> sprite;
    float speed;
    int hp;
    float teleportTimer;
    float teleportInterval;
    HeadConfig config;
    bool movingRight;

public:
    TeleportingHead(const std::string& textureFile, float initialSpeed, const HeadConfig& cfg = {})
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

    void move(float dt) {
        if (!sprite) return;
        teleportTimer += dt;

        if (teleportTimer >= teleportInterval) {
            teleportTimer = 0.f;

            float newX = static_cast<float>(std::rand() % 600 + 50); // stay within screen
            float newY = static_cast<float>(std::rand() % 300 + 20); // don't jump off top
            sprite -> setPosition(sf::Vector2f(newX, newY));
            sprite->setScale(sf::Vector2f(-std::abs(config.scale),
                config.scale
            ));
        }
        else {
            sprite ->move({ 0.f, speed * dt }); // still creeps down slowly
        }

    }

    bool checkBulletHit(const sf::RectangleShape & bullet) {
            if (!sprite) return false;

            if (sprite->getGlobalBounds().findIntersection(bullet.getGlobalBounds()).has_value()) {
                hp--;
                return true;
            }
            return false;
     }

    bool isAlive() const {
            return hp > 0;
     }

    bool hasReachedBottom(float windowHeight) const {
            if (!sprite) return false;

            float headBottom = sprite->getPosition().y + sprite->getTexture().getSize().y * sprite->getScale().y;
            return headBottom >= windowHeight;
     }

    void draw(sf::RenderWindow & window) const {
        if (sprite) {
            window.draw(*sprite);
        };
        
    }
};