#include "Target.h"

Target::Target(float x, float y) {
    shape.setRadius(TARGET_SIZE / 2);
    shape.setOrigin(TARGET_SIZE / 2, TARGET_SIZE / 2);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Red);
}