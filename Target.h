#pragma once
#include <SFML/Graphics.hpp>

const int TARGET_SIZE = 30;

class Target {
public:
    Target(float x, float y);

    sf::CircleShape shape;
};