#pragma once
#include <SFML/Graphics.hpp>
#include "Mirror.h"
#include "Target.h"
#include <vector>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float LASER_SPEED = 0.5f;

class Laser {
public:
    Laser();

    void update(std::vector<Mirror>& mirrors, std::vector<Target>& targets);
    void shoot(float angleDegrees);

    sf::CircleShape shape;
    float angle;
    bool alive;
};