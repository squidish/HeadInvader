
#include "HeadInvaderGame.h"
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

HeadInvaderGame::HeadInvaderGame()
    : window(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), "HeadInvader"),
    playerSpeed(300.f), bulletActive(false), gameOver(false), win(false) {
    setupTexts();
}

void HeadInvaderGame::run() {
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

void HeadInvaderGame::setupTexts() {

   /* if (!font.loadFromFile("arialceb.ttf")) {
        std::cerr << "[ERROR] Could not load font 'arialceb.ttf'\n";
        exit(EXIT_FAILURE);
    } */
    font = sf::Font("arialceb.ttf");
    menuText = sf::Text(font);
    menuText-> setString("Choose your Head!\n1 - Big Red Head\n2 - Blue Angry Head\n3 - Golden Supreme Head\n4 - Load your own (type filename)\nPress 1, 2, 3 or 4");
    menuText->setFillColor(sf::Color::White);
    menuText->setPosition(sf::Vector2f(50.f, 100.f));

    winText = sf::Text(font);
    winText->setString("YOU WIN!");
    winText->setFillColor(sf::Color::White);
    winText->setPosition(sf::Vector2f(WINDOW_WIDTH / 2.f - 120.f, WINDOW_HEIGHT / 2.f - 50.f));

    loseText = sf::Text(font);
    loseText->setString("YOU LOSE!");
    loseText->setFillColor(sf::Color::Red);
    loseText->setPosition(sf::Vector2f(WINDOW_WIDTH / 2.f - 130.f, WINDOW_HEIGHT / 2.f - 50.f));

    restartText = sf::Text(font);
    restartText->setString("Press R to Restart");
    restartText->setFillColor(sf::Color::White);
    restartText->setPosition(sf::Vector2f(WINDOW_WIDTH / 2.f - 150.f, WINDOW_HEIGHT / 2.f + 20.f));
}

void HeadInvaderGame::selectHead() {
    bool headSelected = false;
    while (window.isOpen() && !headSelected) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (event->is<sf::Event::KeyPressed>()) {
                auto key = event->getIf<sf::Event::KeyPressed>()->code;
                if (key == sf::Keyboard::Key::Num1) {
                    selectedHeadTextureFile = "RickAndM.png";
                    headSelected = true;
                }
                else if (key == sf::Keyboard::Key::Num2) {
                    selectedHeadTextureFile = "EasterHead.png";
                    headSelected = true;
                }
                else if (key == sf::Keyboard::Key::Num3) {
                    selectedHeadTextureFile = "Me.png";
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

void HeadInvaderGame::setupGame() {
    player.setSize(sf::Vector2f(60.f, 20.f));
    player.setFillColor(sf::Color::Green);
    player.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.f - 30.f, WINDOW_HEIGHT - 40.f));

    bullet.setSize(sf::Vector2f(5.f, 15.f));
    bullet.setFillColor(sf::Color::Yellow);
    bulletActive = false;
    bulletVelocity = sf::Vector2f(0.f, -400.f);

    head.emplace(selectedHeadTextureFile, 100.f);
    //head.setTexture(selectedHeadTextureFile);

     gameOver = false;
    win = false;
}

void HeadInvaderGame::handleEvents() {
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

void HeadInvaderGame::update(float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && player.getPosition().x > 0)
        player.move(sf::Vector2f(-playerSpeed * dt, 0.f));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && player.getPosition().x + player.getSize().x < WINDOW_WIDTH)
        player.move(sf::Vector2f(playerSpeed * dt, 0.f));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !bulletActive && head && head->isAlive()) {
        bullet.setPosition(sf::Vector2f(
            player.getPosition().x + player.getSize().x / 2.f - bullet.getSize().x / 2.f,
            player.getPosition().y
        ));
        bulletActive = true;
    }

    if (bulletActive) {
        bullet.move(bulletVelocity * dt);
        if (bullet.getPosition().y < 0.f)
            bulletActive = false;

        if (head && head->isAlive() && head->checkBulletHit(bullet)) {
            bulletActive = false;
            if (!head->isAlive()) {
                gameOver = true;
                win = true;
            }
        }
    }

    if (head && head->isAlive()) {
        head->move(dt);
        if (head->hasReachedBottom(static_cast<float>(WINDOW_HEIGHT))) {
            gameOver = true;
            win = false;
        }
    }
}

void HeadInvaderGame::render() {
    window.clear();

    if (!gameOver) {
        if (head)
            head->draw(window);
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


