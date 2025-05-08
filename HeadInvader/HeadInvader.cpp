
#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <string>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int INVADER_HITPOINTS = 20;


class HeadInvaderGame {
public:
    HeadInvaderGame() : window(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), "HeadInvader"), playerSpeed(300.f), bulletActive(false), headAlive(true), headSpeed(100.f), moveRight(true), gameOver(false), win(false) {
        setupTexts();
    }

    void run() {
        selectHead();
        setupGame();

        sf::Clock clock;
        while (window.isOpen()) {
            float dt = clock.restart().asSeconds();
            handleEvents();
            if (!gameOver) {
                update(dt);
            }
            render();
        }
    }
private:
    sf::RenderWindow window;
    sf::RectangleShape player;
    sf::RectangleShape bullet;
    bool bulletActive;
    sf::Vector2f bulletVelocity;
    sf::Texture headTexture;
    std::optional<sf::Sprite> headSprite;
    int headHP;
    bool headAlive;
    float headSpeed;
    bool moveRight;
    float playerSpeed;
    bool gameOver;
    bool win;
    std::string selectedHeadTextureFile;
    std::optional<sf::Text> menuText;
    std::optional<sf::Text> winText;
    std::optional<sf::Text> loseText;
    std::optional<sf::Text> restartText;
    sf::Font font;

    void setupTexts() {
        font = sf::Font("arialceb.ttf");
        menuText = sf::Text(font);
        menuText -> setString("Choose your Head!\n1 - Big Red Head\n2 - Blue Angry Head\n3 - Golden Supreme Head\n4 - Load your own(type filename)\nPress 1, 2, 3 or 4");
        menuText -> setCharacterSize(30);
        menuText -> setFillColor(sf::Color::White);
        menuText -> setPosition(sf::Vector2f(50.f, 100.f));

        winText = sf::Text(font);
        winText -> setFont(font);
        winText -> setString("YOU WIN!");
        winText -> setCharacterSize(50);
        winText -> setFillColor(sf::Color::White);
        winText -> setPosition(sf::Vector2f(static_cast<float>(WINDOW_WIDTH / 2 - 120), static_cast<float>(WINDOW_HEIGHT / 2 - 50)));

        loseText = sf::Text(font);
        loseText -> setFont(font);
        loseText -> setString("YOU LOSE!");
        loseText -> setCharacterSize(50);
        loseText -> setFillColor(sf::Color::Red);
        loseText -> setPosition(sf::Vector2f(static_cast<float>(WINDOW_WIDTH / 2 - 130), static_cast<float>(WINDOW_HEIGHT / 2 - 50)));

        restartText = sf::Text(font);
        restartText -> setFont(font);
        restartText -> setString("Press R to Restart");
        restartText -> setCharacterSize(30);
        restartText -> setFillColor(sf::Color::White);
        restartText -> setPosition(sf::Vector2f(static_cast<float>(WINDOW_WIDTH / 2 - 150), static_cast<float>(WINDOW_HEIGHT / 2 + 20))); 
    }
    void selectHead() {
        bool headSelected = false;
        while (window.isOpen() && !headSelected) {
            while (const std::optional<sf::Event> event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>())
                    window.close();
                if (event->is<sf::Event::KeyPressed>()) {
                    auto key = event->getIf<sf::Event::KeyPressed>()->code;
                    if (key == sf::Keyboard::Key::Num1) {
                        selectedHeadTextureFile = "head.png";
                        headSelected = true;
                    }
                    else if (key == sf::Keyboard::Key::Num2) {
                        selectedHeadTextureFile = "head.png";  
                        headSelected = true;
                    }
                    else if (key == sf::Keyboard::Key::Num3) {
                        selectedHeadTextureFile = "head.png";
                        headSelected = true;
                    } 
                    else if (key == sf::Keyboard::Key::Num4) {
                        std::cout << "Enter the filename of your custom head sprite (e.g., myhead.png): ";
                        std::getline(std::cin, selectedHeadTextureFile);
                        headSelected = true;
                    }
                }
            }
            window.clear();
            if (menuText)
                window.draw(*menuText);
            window.display();
        }   

        if (!headSelected) exit(0);
    }

    void setupGame() {
        player.setSize(sf::Vector2f(60, 20));
        player.setFillColor(sf::Color::Green);
        player.setPosition(sf::Vector2f(static_cast<float>(WINDOW_WIDTH / 2 - 30), static_cast<float>(WINDOW_HEIGHT - 40)));

        bullet.setSize(sf::Vector2f(5, 15));
        bullet.setFillColor(sf::Color::Yellow);
        bulletActive = false;
        bulletVelocity = sf::Vector2f(0.f, -400.f);

        if (!headTexture.loadFromFile(selectedHeadTextureFile)) {
            std::cerr << "[ERROR] Could not load sprite '" << selectedHeadTextureFile << "'\n";
            exit(EXIT_FAILURE);
        }
        headSprite = sf::Sprite(headTexture);
        headSprite->setScale(sf::Vector2f(0.3f, 0.3f));
        headSprite->setPosition(sf::Vector2f(static_cast<float>(WINDOW_WIDTH / 2 - 60), 80.f));

        headHP = INVADER_HITPOINTS;
        headAlive = true;
        headSpeed = 100.f;
        moveRight = true;
        gameOver = false;
        win = false;
    }

    void handleEvents() {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (event->is<sf::Event::KeyPressed>()) {
                auto key = event->getIf<sf::Event::KeyPressed>()->code;
                if (gameOver && key == sf::Keyboard::Key::R) {
                    setupGame();
                }
            }
        }
    }


    void update(float dt) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && player.getPosition().x > 0) {
            player.move(sf::Vector2f(-playerSpeed * dt, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && player.getPosition().x + player.getSize().x < WINDOW_WIDTH) {
            player.move(sf::Vector2f(playerSpeed * dt, 0));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !bulletActive && headAlive) {
            bullet.setPosition(sf::Vector2f(player.getPosition().x + player.getSize().x / 2.f - bullet.getSize().x / 2.f, player.getPosition().y));
            bulletActive = true;
        }

        if (bulletActive) {
            bullet.move(bulletVelocity * dt);
            if (bullet.getPosition().y < 0) bulletActive = false;

            if (headAlive && bullet.getGlobalBounds().findIntersection(headSprite->getGlobalBounds()).has_value()) {
                headHP--;
                bulletActive = false;
                if (headHP <= 0) {
                    headAlive = false;
                    gameOver = true;
                    win = true;
                }
            }
        }

        if (headAlive) {
            float dx = headSpeed * dt * (moveRight ? 1.f : -1.f);
            headSprite->move(sf::Vector2f(dx, 0));

            if (headSprite->getPosition().x <= 0) {
                moveRight = true;
                headSprite->move(sf::Vector2f(0, 20));
                headSpeed += 10.f;
            }

            //float width = static_cast<float>(headSprite->getTexture() -> getSize().x) * headSprite->getScale().x;
            float width = static_cast<float>(headSprite->getTexture().getSize().x) * headSprite->getScale().x;
            if (headSprite->getPosition().x + width >= WINDOW_WIDTH) {
                moveRight = false;
                headSprite->move(sf::Vector2f(0, 20));
                headSpeed += 10.f;
            }

            //float headBottom = headSprite->getPosition().y + headSprite->getTexture()->getSize().y * headSprite->getScale().y;
            float headBottom = headSprite->getPosition().y + headSprite->getTexture().getSize().y * headSprite->getScale().y;
            if (headBottom >= WINDOW_HEIGHT) {
                headAlive = false;
                gameOver = true;
                win = false;
            }
        }
    }


    void render() {
        window.clear();

        if (!gameOver) {
            if (headSprite)
                window.draw(*headSprite);
        }
        else {
            if (win && winText) {
                window.draw(*winText);
            }
            else if (loseText) {
                window.draw(*loseText);
            }
            if (restartText)
                window.draw(*restartText);
        }

        window.draw(player);
        if (bulletActive) window.draw(bullet);

        window.display();
    }



};

int main() {
	HeadInvaderGame game;
    game.run();
	return 0;
} 

