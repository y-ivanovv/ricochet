#include "Mirror.h"

Mirror::Mirror(float x, float y, float angle) : angle(angle) {
    shape.setSize(sf::Vector2f(MIRROR_SIZE, 2));
    shape.setOrigin(MIRROR_SIZE / 2, 1);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);
    shape.setRotation(angle);
}

void Mirror::rotateClockwise() {
    angle += 30.0f;
    shape.rotate(30.0f);
}