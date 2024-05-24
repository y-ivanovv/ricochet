#include "Utilities.h"
#include <random>
#include <cmath>

float randomFloat(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}

bool isTooClose(const std::vector<Mirror>& mirrors, sf::Vector2f point, float minDistance) {
    for (const auto& mirror : mirrors) {
        if (std::hypot(mirror.shape.getPosition().x - point.x, mirror.shape.getPosition().y - point.y) < minDistance) {
            return true;
        }
    }
    return false;
}