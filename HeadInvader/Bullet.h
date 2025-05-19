
constexpr float BULLET_WIDTH = 5.f;
constexpr float BULLET_HEIGHT = 15.f;
constexpr float BULLET_SPEED = -400.f;

class Bullet {

public:

    sf::RectangleShape shape;
    sf::Vector2f velocity;

    Bullet(const sf::Vector2f& pos) {
        shape.setSize({ BULLET_WIDTH, BULLET_HEIGHT });
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition(pos);
        velocity = { 0.f, BULLET_SPEED };
    }

    void update(float dt) {
        shape.move(velocity * dt);
    }

    bool isOffScreen() const {
        return shape.getPosition().y + BULLET_HEIGHT < 0.f;
    }
};
