#pragma once
#include <SFML/Graphics.hpp>

const int MIRROR_SIZE = 50;

class Mirror {
public:
    Mirror(float x, float y, float angle);

    void rotateClockwise();

    sf::RectangleShape shape;
    float angle;
};