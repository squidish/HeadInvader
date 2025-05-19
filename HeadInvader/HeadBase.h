class HeadBase {
public:
    virtual ~HeadBase() = default;

    virtual void move(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual bool checkBulletHit(const sf::RectangleShape& bullet) = 0;
    virtual bool isAlive() const = 0;
    virtual bool hasReachedBottom(float windowHeight) const = 0;
};
