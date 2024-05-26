#pragma once
#include <SFML/Graphics.hpp>
#include "Mirror.h"
#include <vector>

float randomFloat(float min, float max);
bool isTooClose(const std::vector<Mirror>& mirrors, sf::Vector2f point, float minDistance);
