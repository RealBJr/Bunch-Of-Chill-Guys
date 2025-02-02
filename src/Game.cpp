#include "Game.hpp"
#include <cmath>

Game::Game()
    : window(sf::VideoMode(800, 600), "SFML Gunfight Game", sf::Style::Default),
      player1(20, 275, sf::Color::Green),
      player2(730, 275, sf::Color::Blue)
{

    window.setFramerateLimit(60);

    view.setSize(800, 600);
    view.setCenter(400, 300);
    window.setView(view);

    player2.setPosition(window.getSize().x - player2.getRadius() - 20, window.getSize().y / 2 - player2.getRadius() / 2);
    player1.setPosition(20, window.getSize().y / 2 - player1.getRotation() / 2);

    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"))
    {
        // Handle error
    }

    controlsText.setFont(font);
    controlsText.setCharacterSize(14);
    controlsText.setFillColor(sf::Color::White);
    controlsText.setString("P1: Move (WASD), Shoot (Space) | P2: Move (Arrow Keys), Shoot (Enter)");
    controlsText.setPosition(10, window.getSize().y - 20);
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::Resized)
        {
            handleResize(event.size.width, event.size.height);

            // Adjust players to stay near the edges
            player1.setPosition(20, window.getSize().y / 2 - player1.getRadius() / 2);                                            // Slightly from the left edge, vertically centered
            player2.setPosition(window.getSize().x - player2.getRadius() - 20, window.getSize().y / 2 - player2.getRadius() / 2); // Slightly from the right edge, vertically centered

            // Adjust controls text position when resizing
            controlsText.setPosition(10, window.getSize().y - 20);
        }
    }
    handleShooting();
}

void Game::handleResize(int windowWidth, int windowHeight)
{
    view.setSize(windowWidth, windowHeight);
    view.setCenter(windowWidth / 2, windowHeight / 2);
    window.setView(view);

    controlsText.setPosition(10, windowHeight - 20);
}

void Game::update()
{
    player1.update(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, window);
    player2.update(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, window);

    for (auto &bullet : bullets)
    {
        bullet.update();
    }
}

void Game::render()
{
    window.clear();
    player1.draw(window);
    player2.draw(window);

    for (auto &bullet : bullets)
    {
        bullet.draw(window);
    }

    // Draw controls at the bottom of the screen
    window.draw(controlsText);

    window.display();
}

float toRadians(float degrees)
{
    return degrees * M_PI / 180.0f;
}

void Game::handleShooting()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        shoot(player1);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        shoot(player2);
    }
}

void Game::shoot(Player &player)
{
    // Get the player's rotation in degrees
    float rotation = player.getRotation();

    // Convert rotation to radians
    float radians = toRadians(rotation);

    // Calculate the bullet's direction (unit vector)
    float dirX = std::cos(radians);
    float dirY = std::sin(radians);

    // Calculate the bullet's initial position (offset from the player's center)
    float offset = player.getRadius() / 2; // Offset by half the player's width
    float bulletX = player.getPosition().x + dirX * offset;
    float bulletY = player.getPosition().y + dirY * offset;

    // Set the bullet's velocity (scaled by a speed factor)
    float bulletSpeed = 1.0f; // Adjust as needed
    float velX = dirX * bulletSpeed;
    float velY = dirY * bulletSpeed;

    // Shoot the bullet
    bullets.push_back(Bullet(bulletX, bulletY, velX, velY));
}
