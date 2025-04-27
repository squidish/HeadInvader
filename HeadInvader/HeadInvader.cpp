
/*
#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>
#include <random>
#include <optional>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int INVADER_HITPOINTS = 20;

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), "HeadInvader");

    // Player setup
    sf::RectangleShape player(sf::Vector2f(60, 20));
    player.setFillColor(sf::Color::Green);
    player.setPosition(sf::Vector2f(
        static_cast<float>(WINDOW_WIDTH / 2 - 30),
        static_cast<float>(WINDOW_HEIGHT - 40)
    ));

    float playerSpeed = 300.f;

    // Bullet setup
    sf::RectangleShape bullet(sf::Vector2f(5, 15));
    bullet.setFillColor(sf::Color::Yellow);
    bool bulletActive = false;
    sf::Vector2f bulletVelocity(0.f, -400.f);

    // Head Invader sprite setup
    sf::Texture headTexture("head.png");
    sf::Sprite headSprite(headTexture);

    try {
        headTexture = sf::Texture("head.png");
    }
    catch (const std::exception& e) {
        std::cerr << "[ERROR] Could not load sprite 'head.png': " << e.what() << "\n";
        return EXIT_FAILURE;
    }
    headSprite.setTexture(headTexture);
    headSprite.setScale(sf::Vector2f(0.3f, 0.3f));
    headSprite.setPosition(sf::Vector2f(static_cast<float>(WINDOW_WIDTH / 2 - 60), 80.f));

    int headHP = INVADER_HITPOINTS;
    bool headAlive = true;
    float headSpeed = 100.f;
    bool moveRight = true;

    sf::Font font;
    try {
        font = sf::Font("arialceb.ttf");
    }
    catch (const std::exception& e) {
        std::cerr << "[ERROR] Could not load font 'arialceb.ttf': " << e.what() << "\n";
        std::cerr << "Make sure the font file is in the correct directory.\n";
        return EXIT_FAILURE;
    }
    sf::Text winText(font);
    winText.setString("YOU WIN!");
    winText.setCharacterSize(50);
    winText.setFillColor(sf::Color::White);
    winText.setPosition(sf::Vector2f(static_cast<float>(WINDOW_WIDTH / 2 - 120), static_cast<float>(WINDOW_HEIGHT / 2 - 50)));

    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Player movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && player.getPosition().x > 0) {
            player.move(sf::Vector2f(-playerSpeed * dt, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && player.getPosition().x + player.getSize().x < WINDOW_WIDTH) {
            player.move(sf::Vector2f(playerSpeed * dt, 0));
        }

        // Shooting
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !bulletActive && headAlive) {
            bullet.setPosition(sf::Vector2f(
                player.getPosition().x + player.getSize().x / 2.f - bullet.getSize().x / 2.f,
                player.getPosition().y)
            );
            bulletActive = true;
        }

        // Bullet movement
        if (bulletActive) {
            bullet.move(bulletVelocity * dt);
            if (bullet.getPosition().y < 0) bulletActive = false;

            if (headAlive && bullet.getGlobalBounds().findIntersection(headSprite.getGlobalBounds()).has_value()) {
                headHP--;
                bulletActive = false;
                std::cout << "Hit! HP left: " << headHP << "\n";
                if (headHP <= 0) {
                    headAlive = false;
                    std::cout << "Head Invader defeated!\n";
                }
            }
        }

        // Head movement
        if (headAlive) {
            float dx = headSpeed * dt * (moveRight ? 1.f : -1.f);
            headSprite.move(sf::Vector2f(dx, 0));
            if (headSprite.getPosition().x <= 0) moveRight = true;
            float width = static_cast<float>(headSprite.getTexture().getSize().x) * headSprite.getScale().x;
            if (headSprite.getPosition().x + width >= WINDOW_WIDTH)
                moveRight = false;
        }

        // Rendering
        window.clear();

        if (headAlive) {
            window.draw(headSprite);
        }
        else {
            window.draw(winText);
        }

        window.draw(player);
        if (bulletActive) window.draw(bullet);

        window.display();
    }

    return 0;
}

*/
/*
#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>
#include <random>
#include <optional>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int INVADER_HITPOINTS = 20;

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), "HeadInvader");

    // Font setup for menu and win text
    sf::Font font;
    try {
        font = sf::Font("arialceb.ttf");
    }
    catch (const std::exception& e) {
        std::cerr << "[ERROR] Could not load font 'arialceb.ttf': " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    sf::Text menuText(font);
    menuText.setString("Choose your Head!\n1 - Big Red Head\n2 - Blue Angry Head\n3 - Golden Supreme Head\nPress 1, 2 or 3");
    menuText.setCharacterSize(30);
    menuText.setFillColor(sf::Color::White);
    menuText.setPosition(sf::Vector2f(50.f, 100.f));

    // Menu loop before the game starts
    std::string selectedHeadTextureFile;
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
            }
        }

        window.clear();
        window.draw(menuText);
        window.display();
    }

    if (!headSelected) return 0; // Exit if window closed at menu

    // Player setup
    sf::RectangleShape player(sf::Vector2f(60, 20));
    player.setFillColor(sf::Color::Green);
    player.setPosition(sf::Vector2f(
        static_cast<float>(WINDOW_WIDTH / 2 - 30),
        static_cast<float>(WINDOW_HEIGHT - 40)
    ));

    float playerSpeed = 300.f;

    // Bullet setup
    sf::RectangleShape bullet(sf::Vector2f(5, 15));
    bullet.setFillColor(sf::Color::Yellow);
    bool bulletActive = false;
    sf::Vector2f bulletVelocity(0.f, -400.f);

    // Head Invader sprite setup
    sf::Texture headTexture;
    try {
        headTexture = sf::Texture(selectedHeadTextureFile);
    }
    catch (const std::exception& e) {
        std::cerr << "[ERROR] Could not load sprite '" << selectedHeadTextureFile << "': " << e.what() << "\n";
        return EXIT_FAILURE;
    }
    sf::Sprite headSprite(headTexture);
    headSprite.setScale(sf::Vector2f(0.3f, 0.3f));
    headSprite.setPosition(sf::Vector2f(static_cast<float>(WINDOW_WIDTH / 2 - 60), 80.f));

    int headHP = INVADER_HITPOINTS;
    bool headAlive = true;
    float headSpeed = 100.f;
    bool moveRight = true;

    sf::Text winText(font);
    winText.setString("YOU WIN!");
    winText.setCharacterSize(50);
    winText.setFillColor(sf::Color::White);
    winText.setPosition(sf::Vector2f(static_cast<float>(WINDOW_WIDTH / 2 - 120), static_cast<float>(WINDOW_HEIGHT / 2 - 50)));

    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Player movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && player.getPosition().x > 0) {
            player.move(sf::Vector2f(-playerSpeed * dt, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && player.getPosition().x + player.getSize().x < WINDOW_WIDTH) {
            player.move(sf::Vector2f(playerSpeed * dt, 0));
        }

        // Shooting
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !bulletActive && headAlive) {
            bullet.setPosition(sf::Vector2f(
                player.getPosition().x + player.getSize().x / 2.f - bullet.getSize().x / 2.f,
                player.getPosition().y)
            );
            bulletActive = true;
        }

        // Bullet movement
        if (bulletActive) {
            bullet.move(bulletVelocity * dt);
            if (bullet.getPosition().y < 0) bulletActive = false;

            if (headAlive && bullet.getGlobalBounds().findIntersection(headSprite.getGlobalBounds()).has_value()) {
                headHP--;
                bulletActive = false;
                std::cout << "Hit! HP left: " << headHP << "\n";
                if (headHP <= 0) {
                    headAlive = false;
                    std::cout << "Head Invader defeated!\n";
                }
            }
        }

        // Head movement
        if (headAlive) {
            float dx = headSpeed * dt * (moveRight ? 1.f : -1.f);
            headSprite.move(sf::Vector2f(dx, 0));
            if (headSprite.getPosition().x <= 0) moveRight = true;
            float width = static_cast<float>(headSprite.getTexture().getSize().x) * headSprite.getScale().x;
            if (headSprite.getPosition().x + width >= WINDOW_WIDTH)
                moveRight = false;
        }

        // Rendering
        window.clear();

        if (headAlive) {
            window.draw(headSprite);
        }
        else {
            window.draw(winText);
        }

        window.draw(player);
        if (bulletActive) window.draw(bullet);

        window.display();
    }

    return 0;
}*/
/*
#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>
#include <random>
#include <optional>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int INVADER_HITPOINTS = 20;

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), "HeadInvader");

    // Font setup for menu and win/lose text
    sf::Font font;
    try {
        font = sf::Font("arialceb.ttf");
    }
    catch (const std::exception& e) {
        std::cerr << "[ERROR] Could not load font 'arialceb.ttf': " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    sf::Text menuText(font);
    menuText.setString("Choose your Head!\n1 - Big Red Head\n2 - Blue Angry Head\n3 - Golden Supreme Head\nPress 1, 2 or 3");
    menuText.setCharacterSize(30);
    menuText.setFillColor(sf::Color::White);
    menuText.setPosition(sf::Vector2f(50.f, 100.f));

    // Menu loop before the game starts
    std::string selectedHeadTextureFile;
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
            }
        }

        window.clear();
        window.draw(menuText);
        window.display();
    }

    if (!headSelected) return 0; // Exit if window closed at menu

restart_game:

    // Player setup
    sf::RectangleShape player(sf::Vector2f(60, 20));
    player.setFillColor(sf::Color::Green);
    player.setPosition(sf::Vector2f(
        static_cast<float>(WINDOW_WIDTH / 2 - 30),
        static_cast<float>(WINDOW_HEIGHT - 40)
    ));

    float playerSpeed = 300.f;

    // Bullet setup
    sf::RectangleShape bullet(sf::Vector2f(5, 15));
    bullet.setFillColor(sf::Color::Yellow);
    bool bulletActive = false;
    sf::Vector2f bulletVelocity(0.f, -400.f);

    // Head Invader sprite setup
    sf::Texture headTexture;
    try {
        headTexture = sf::Texture(selectedHeadTextureFile);
    }
    catch (const std::exception& e) {
        std::cerr << "[ERROR] Could not load sprite '" << selectedHeadTextureFile << "': " << e.what() << "\n";
        return EXIT_FAILURE;
    }
    sf::Sprite headSprite(headTexture);
    headSprite.setScale(sf::Vector2f(0.3f, 0.3f));
    headSprite.setPosition(sf::Vector2f(static_cast<float>(WINDOW_WIDTH / 2 - 60), 80.f));

    int headHP = INVADER_HITPOINTS;
    bool headAlive = true;
    float headSpeed = 1000.f;
    bool moveRight = true;

    sf::Text winText(font);
    winText.setString("YOU WIN!");
    winText.setCharacterSize(50);
    winText.setFillColor(sf::Color::White);
    winText.setPosition(sf::Vector2f(static_cast<float>(WINDOW_WIDTH / 2 - 120), static_cast<float>(WINDOW_HEIGHT / 2 - 50)));

    sf::Text loseText(font);
    loseText.setString("YOU LOSE!");
    loseText.setCharacterSize(50);
    loseText.setFillColor(sf::Color::Red);
    loseText.setPosition(sf::Vector2f(static_cast<float>(WINDOW_WIDTH / 2 - 130), static_cast<float>(WINDOW_HEIGHT / 2 - 50)));

    sf::Text restartText(font);
    restartText.setString("Press R to Restart");
    restartText.setCharacterSize(30);
    restartText.setFillColor(sf::Color::White);
    restartText.setPosition(sf::Vector2f(static_cast<float>(WINDOW_WIDTH / 2 - 150), static_cast<float>(WINDOW_HEIGHT / 2 + 20)));

    bool gameOver = false;
    bool win = false;

    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (event->is<sf::Event::KeyPressed>()) {
                auto key = event->getIf<sf::Event::KeyPressed>()->code;
                if (gameOver && key == sf::Keyboard::Key::R) {
                    goto restart_game;
                }
            }
        }

        if (!gameOver) {
            // Player movement
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && player.getPosition().x > 0) {
                player.move(sf::Vector2f(-playerSpeed * dt, 0));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && player.getPosition().x + player.getSize().x < WINDOW_WIDTH) {
                player.move(sf::Vector2f(playerSpeed * dt, 0));
            }

            // Shooting
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !bulletActive && headAlive) {
                bullet.setPosition(sf::Vector2f(
                    player.getPosition().x + player.getSize().x / 2.f - bullet.getSize().x / 2.f,
                    player.getPosition().y)
                );
                bulletActive = true;
            }

            // Bullet movement
            if (bulletActive) {
                bullet.move(bulletVelocity * dt);
                if (bullet.getPosition().y < 0) bulletActive = false;

                if (headAlive && bullet.getGlobalBounds().findIntersection(headSprite.getGlobalBounds()).has_value()) {
                    headHP--;
                    bulletActive = false;
                    std::cout << "Hit! HP left: " << headHP << "\n";
                    if (headHP <= 0) {
                        headAlive = false;
                        gameOver = true;
                        win = true;
                        std::cout << "Head Invader defeated!\n";
                    }
                }
            }

            // Head movement
            if (headAlive) {
                float dx = headSpeed * dt * (moveRight ? 1.f : -1.f);
                headSprite.move(sf::Vector2f(dx, 0));
                if (headSprite.getPosition().x <= 0) moveRight = true;
                float width = static_cast<float>(headSprite.getTexture().getSize().x) * headSprite.getScale().x;
                if (headSprite.getPosition().x + width >= WINDOW_WIDTH)
                    moveRight = false;

                float headBottom = headSprite.getPosition().y + headSprite.getTexture().getSize().y * headSprite.getScale().y;
                if (headBottom >= WINDOW_HEIGHT) {
                    headAlive = false;
                    gameOver = true;
                    win = false;
                    std::cout << "Head reached the bottom. You lose!\n";
                }
            }
        }

        // Rendering
        window.clear();

        if (!gameOver) {
            window.draw(headSprite);
        }
        else {
            if (win) {
                window.draw(winText);
            }
            else {
                window.draw(loseText);
            }
            window.draw(restartText);
        }

        window.draw(player);
        if (bulletActive) window.draw(bullet);

        window.display();
    }

    return 0;
}*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>
#include <random>
#include <optional>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int INVADER_HITPOINTS = 20;

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), "HeadInvader");

    // Font setup for menu and win/lose text
    sf::Font font;
    try {
        font = sf::Font("arialceb.ttf");
    }
    catch (const std::exception& e) {
        std::cerr << "[ERROR] Could not load font 'arialceb.ttf': " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    sf::Text menuText(font);
    menuText.setString("Choose your Head!\n1 - Big Red Head\n2 - Blue Angry Head\n3 - Golden Supreme Head\nPress 1, 2 or 3");
    menuText.setCharacterSize(30);
    menuText.setFillColor(sf::Color::White);
    menuText.setPosition(sf::Vector2f(50.f, 100.f));

    // Menu loop before the game starts
    std::string selectedHeadTextureFile;
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
            }
        }

        window.clear();
        window.draw(menuText);
        window.display();
    }

    if (!headSelected) return 0; // Exit if window closed at menu

restart_game:

    // Player setup
    sf::RectangleShape player(sf::Vector2f(60, 20));
    player.setFillColor(sf::Color::Green);
    player.setPosition(sf::Vector2f(
        static_cast<float>(WINDOW_WIDTH / 2 - 30),
        static_cast<float>(WINDOW_HEIGHT - 40)
    ));

    float playerSpeed = 300.f;

    // Bullet setup
    sf::RectangleShape bullet(sf::Vector2f(5, 15));
    bullet.setFillColor(sf::Color::Yellow);
    bool bulletActive = false;
    sf::Vector2f bulletVelocity(0.f, -400.f);

    // Head Invader sprite setup
    sf::Texture headTexture;
    try {
        headTexture = sf::Texture(selectedHeadTextureFile);
    }
    catch (const std::exception& e) {
        std::cerr << "[ERROR] Could not load sprite '" << selectedHeadTextureFile << "': " << e.what() << "\n";
        return EXIT_FAILURE;
    }
    sf::Sprite headSprite(headTexture);
    headSprite.setScale(sf::Vector2f(0.3f, 0.3f));
    headSprite.setPosition(sf::Vector2f(static_cast<float>(WINDOW_WIDTH / 2 - 60), 80.f));

    int headHP = INVADER_HITPOINTS;
    bool headAlive = true;
    float headSpeed = 100.f;
    bool moveRight = true;

    sf::Text winText(font);
    winText.setString("YOU WIN!");
    winText.setCharacterSize(50);
    winText.setFillColor(sf::Color::White);
    winText.setPosition(sf::Vector2f(static_cast<float>(WINDOW_WIDTH / 2 - 120), static_cast<float>(WINDOW_HEIGHT / 2 - 50)));

    sf::Text loseText(font);
    loseText.setString("YOU LOSE!");
    loseText.setCharacterSize(50);
    loseText.setFillColor(sf::Color::Red);
    loseText.setPosition(sf::Vector2f(static_cast<float>(WINDOW_WIDTH / 2 - 130), static_cast<float>(WINDOW_HEIGHT / 2 - 50)));

    sf::Text restartText(font);
    restartText.setString("Press R to Restart");
    restartText.setCharacterSize(30);
    restartText.setFillColor(sf::Color::White);
    restartText.setPosition(sf::Vector2f(static_cast<float>(WINDOW_WIDTH / 2 - 150), static_cast<float>(WINDOW_HEIGHT / 2 + 20)));

    bool gameOver = false;
    bool win = false;

    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (event->is<sf::Event::KeyPressed>()) {
                auto key = event->getIf<sf::Event::KeyPressed>()->code;
                if (gameOver && key == sf::Keyboard::Key::R) {
                    goto restart_game;
                }
            }
        }

        if (!gameOver) {
            // Player movement
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && player.getPosition().x > 0) {
                player.move(sf::Vector2f(-playerSpeed * dt, 0));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && player.getPosition().x + player.getSize().x < WINDOW_WIDTH) {
                player.move(sf::Vector2f(playerSpeed * dt, 0));
            }

            // Shooting
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !bulletActive && headAlive) {
                bullet.setPosition(sf::Vector2f(
                    player.getPosition().x + player.getSize().x / 2.f - bullet.getSize().x / 2.f,
                    player.getPosition().y)
                );
                bulletActive = true;
            }

            // Bullet movement
            if (bulletActive) {
                bullet.move(bulletVelocity * dt);
                if (bullet.getPosition().y < 0) bulletActive = false;

                if (headAlive && bullet.getGlobalBounds().findIntersection(headSprite.getGlobalBounds()).has_value()) {
                    headHP--;
                    bulletActive = false;
                    std::cout << "Hit! HP left: " << headHP << "\n";
                    if (headHP <= 0) {
                        headAlive = false;
                        gameOver = true;
                        win = true;
                        std::cout << "Head Invader defeated!\n";
                    }
                }
            }

            // Head movement
            if (headAlive) {
                float dx = headSpeed * dt * (moveRight ? 1.f : -1.f);
                headSprite.move(sf::Vector2f(dx, 0));
                if (headSprite.getPosition().x <= 0) {
                    moveRight = true;
                    headSprite.move(sf::Vector2f(0, 20)); // Move down when hit left wall
                    headSpeed += 10.f; // Speed up
                }
                float width = static_cast<float>(headSprite.getTexture().getSize().x) * headSprite.getScale().x;
                if (headSprite.getPosition().x + width >= WINDOW_WIDTH) {
                    moveRight = false;
                    headSprite.move(sf::Vector2f(0, 20)); // Move down when hit right wall
                    headSpeed += 10.f; // Speed up
                }

                float headBottom = headSprite.getPosition().y + headSprite.getTexture().getSize().y * headSprite.getScale().y;
                if (headBottom >= WINDOW_HEIGHT) {
                    headAlive = false;
                    gameOver = true;
                    win = false;
                    std::cout << "Head reached the bottom. You lose!\n";
                }
            }
        }

        // Rendering
        window.clear();

        if (!gameOver) {
            window.draw(headSprite);
        }
        else {
            if (win) {
                window.draw(winText);
            }
            else {
                window.draw(loseText);
            }
            window.draw(restartText);
        }

        window.draw(player);
        if (bulletActive) window.draw(bullet);

        window.display();
    }

    return 0;
}





