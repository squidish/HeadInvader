

#include "HeadInvaderGame.h"
#include <iostream>
#include <map>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Game constants
constexpr float PLAYER_WIDTH = 60.f;
constexpr float PLAYER_HEIGHT = 20.f;
constexpr float PLAYER_SPEED = 300.f;


constexpr sf::Vector2f WIN_TEXT_OFFSET = { 120.f, 50.f };
constexpr sf::Vector2f LOSE_TEXT_OFFSET = { 130.f, 50.f };
constexpr sf::Vector2f RESTART_TEXT_OFFSET = { 150.f, -20.f };

HeadInvaderGame::HeadInvaderGame()
    : window(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), "HeadInvader"),
    playerSpeed(PLAYER_SPEED), bulletActive(false), gameOver(false), win(false) {
    setupTexts();
}


void HeadInvaderGame::run() {
    while (window.isOpen()) {
        selectHead();   // Show menu and let player choose head
        setupGame();    // Prepare for gameplay

        sf::Clock clock;
        while (window.isOpen() && !gameOver) {
            float dt = clock.restart().asSeconds();
            handleEvents();
            if (!gameOver) {
                update(dt);
            }
            render();
        }

        // Small delay to show win/lose message before returning to menu
        sf::sleep(sf::seconds(2));
    }
}


void HeadInvaderGame::setupTexts() {
    font = sf::Font("arialceb.ttf");

    menuText = sf::Text(font);
    menuText->setString("Choose your Head!\n1 - Mick and Dorty\n2 - Good Friday Island\n3 - God Emperor Head\n4 - Load your own (type filename)\nPress 1, 2, 3 or 4");
    menuText->setFillColor(sf::Color::White);
    menuText->setPosition({ 50.f, 100.f });

    winText = sf::Text(font);
    winText->setString("YOU WIN!");
    winText->setFillColor(sf::Color::White);
    winText->setPosition({ WINDOW_WIDTH / 2.f - WIN_TEXT_OFFSET.x, WINDOW_HEIGHT / 2.f - WIN_TEXT_OFFSET.y });

    loseText = sf::Text(font);
    loseText->setString("YOU LOSE!");
    loseText->setFillColor(sf::Color::Red);
    loseText->setPosition({ WINDOW_WIDTH / 2.f - LOSE_TEXT_OFFSET.x, WINDOW_HEIGHT / 2.f - LOSE_TEXT_OFFSET.y });

    restartText = sf::Text(font);
    restartText->setString("Press R to Restart");
    restartText->setFillColor(sf::Color::White);
    restartText->setPosition({ WINDOW_WIDTH / 2.f - RESTART_TEXT_OFFSET.x, WINDOW_HEIGHT / 2.f - RESTART_TEXT_OFFSET.y });
}

void HeadInvaderGame::selectHead() {

    music.load("Sounds/StockTune-City Lights Rushing By_1747174226.ogg");
    music.play(true);

    const std::map<sf::Keyboard::Key, std::string> headChoices = {
        {sf::Keyboard::Key::Num1, "Heads/RickAndM.png"},
        {sf::Keyboard::Key::Num2, "Heads/EasterHead.png"},
        {sf::Keyboard::Key::Num3, "Heads/Me.png"}
    };

    bool headSelected = false;
    while (window.isOpen() && !headSelected) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            if (event->is<sf::Event::KeyPressed>()) {
                auto key = event->getIf<sf::Event::KeyPressed>()->code;
                if (auto it = headChoices.find(key); it != headChoices.end()) {
                    selectedHeadTextureFile = it->second;
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
        if (menuText) window.draw(*menuText);
        window.display();
    }

    if (!headSelected) exit(0);
}

void HeadInvaderGame::setupGame() {

    //music.load("C:/Users/chris/source/repos/HeadInvader/HeadInvader/Sounds/StockTune-City Lights Rushing By_1747174226.ogg");
    //music.play(true);

    player.setSize({ PLAYER_WIDTH, PLAYER_HEIGHT });
    player.setFillColor(sf::Color::Green);
    player.setPosition({ WINDOW_WIDTH / 2.f - PLAYER_WIDTH / 2.f, WINDOW_HEIGHT - 40.f });

    /*bullet.setSize({BULLET_WIDTH, BULLET_HEIGHT});
    bullet.setFillColor(sf::Color::Yellow);
    bulletVelocity = { 0.f, BULLET_SPEED };
    bulletActive = false;*/

    head.emplace(selectedHeadTextureFile, 100.f); // Could add config later

    timeSinceLastShot = fireCooldown;

    gameOver = false;
    win = false;
}

void HeadInvaderGame::handleEvents() {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) window.close();

        if (event->is<sf::Event::KeyPressed>()) {
            auto key = event->getIf<sf::Event::KeyPressed>()->code;
            if (gameOver && key == sf::Keyboard::Key::R) {
                setupGame();
            }
        }
    }
}

void HeadInvaderGame::update(float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && player.getPosition().x > 0.f) {
        player.move({ -playerSpeed * dt, 0.f });
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) &&
        player.getPosition().x + player.getSize().x < WINDOW_WIDTH) {
        player.move({ playerSpeed * dt, 0.f });
    }

    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) &&
        !bulletActive && head && head->isAlive()) {
        bullet.setPosition({
            player.getPosition().x + player.getSize().x / 2.f - bullet.getSize().x / 2.f,
            player.getPosition().y
            });
        bulletActive = true;
    }*/

    timeSinceLastShot += dt;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && head && head->isAlive() && timeSinceLastShot >= fireCooldown) {
       
        sf::Vector2f bulletPos = {
            player.getPosition().x + player.getSize().x / 2.f - BULLET_WIDTH / 2.f,
            player.getPosition().y
        };

        bullets.push_back(std::make_unique<Bullet>(bulletPos));
        timeSinceLastShot = 0.f; // Reset cooldown
    }

/*    if (bulletActive) {
        bullet.move(bulletVelocity * dt);
        if (bullet.getPosition().y < 0.f) bulletActive = false;

        if (head && head->isAlive() && head->checkBulletHit(bullet)) {
            bulletActive = false;
            if (!head->isAlive()) {
                gameOver = true;
                win = true;
            }
        }
    } */

    for (auto it = bullets.begin(); it != bullets.end(); ) {
        (*it)->update(dt);

        if ((*it)->isOffScreen()) {
            it = bullets.erase(it);
            continue;
        }

        if (head && head->isAlive() && head->checkBulletHit((*it)->shape)) {
            it = bullets.erase(it);
            if (!head->isAlive()) {
                gameOver = true;
                win = true;
            }
            continue;
        }

        ++it;
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
        if (head) head->draw(window);

        // Draw bullets
        for (const auto& bullet : bullets) {
            window.draw(bullet->shape);
        }
    }
    else {
        if (win && winText) window.draw(*winText);
        else if (loseText) window.draw(*loseText);
        if (restartText) window.draw(*restartText);
    }

    window.draw(player);
    //if (bulletActive) window.draw(bullet);

    window.display();
}



