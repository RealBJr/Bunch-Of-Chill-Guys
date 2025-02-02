#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Player
{
public:
    Player(float x, float y, sf::Color color, const std::string &textureFile = "assets/soldier/soldier1_gun.png");

    void update(sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right, const sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);

    sf::Vector2f getPosition();
    float getRadius();
    void setPosition(float x, float y);
    float getRotation();

private:
    sf::CircleShape shape; // Player rectangle
    sf::Texture texture;   // Texture for the image
    sf::Sprite sprite;     // Sprite for the image
    float speed = 4.0f;    // Movement speed
};

#endif
