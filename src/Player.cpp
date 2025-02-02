#include "Player.hpp"
#include <iostream> // For std::cerr

Player::Player(float x, float y, sf::Color color, const std::string &textureFile)
    : texture(), sprite()
{
    // Load the texture and set the sprite
    if (!texture.loadFromFile(textureFile))
    {
        // Handle the error if the texture is not loaded properly
        std::cerr << "Error loading texture!" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2); // Set sprite origin to center
    // sprite.setPosition(x, y);  // Set sprite position to (x, y)

    // Set up the rectangle shape
    shape.setRadius(sprite.getGlobalBounds().width / 2); // Example size, adjust as needed
    shape.setFillColor(color);
    shape.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
}

void Player::update(sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right, const sf::RenderWindow &window)
{
    if (sf::Keyboard::isKeyPressed(up))
    {
        sprite.setRotation(-90);
        shape.move(0, -speed);
    }
    if (sf::Keyboard::isKeyPressed(down))
    {
        sprite.setRotation(90);
        shape.move(0, speed);
    }
    if (sf::Keyboard::isKeyPressed(left))
    {
        sprite.setRotation(180);
        shape.move(-speed, 0);
    }
    if (sf::Keyboard::isKeyPressed(right))
    {
        sprite.setRotation(0);
        shape.move(speed, 0);
    }

    // Update the sprite position to match the shape
    sprite.setPosition(shape.getPosition());
    // Get the current window size for fullscreen boundaries
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2f pos = shape.getPosition();
    float size = shape.getRadius();

    // Ensure boundary conditions for fullscreen
    if (pos.x < 0)
        shape.setPosition(0, pos.y); // Left boundary
    if (pos.y < 0)
        shape.setPosition(pos.x, 0); // Top boundary
    if (pos.x + size > windowSize.x)
        shape.setPosition(windowSize.x - size, pos.y); // Right boundary
    if (pos.y + size > windowSize.y)
        shape.setPosition(pos.x, windowSize.y - size); // Bottom boundary
}

void Player::draw(sf::RenderWindow &window)
{
    // Draw the player shape
    window.draw(shape);

    // Draw the sprite (image) on top of the player
    window.draw(sprite);
}

sf::Vector2f Player::getPosition()
{
    return shape.getPosition();
}

float Player::getRadius()
{
    return shape.getRadius();
}

float Player::getRotation()
{
    return sprite.getRotation();
}

void Player::setPosition(float x, float y)
{
    shape.setPosition(x, y);
    sprite.setPosition(x, y); // Set the sprite position as well
}
