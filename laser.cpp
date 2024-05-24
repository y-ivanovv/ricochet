#include "Laser.h"
#include <cmath>

Laser::Laser() : alive(false), angle(0.0f) {
    shape.setRadius(5.0f);
    shape.setOrigin(5.0f, 5.0f);
    shape.setFillColor(sf::Color::Green);
}

void Laser::update(std::vector<Mirror>& mirrors, std::vector<Target>& targets) {
    if (!alive) return;

    float dx = std::cos(angle * 3.1415926 / 180.0f) * LASER_SPEED;
    float dy = std::sin(angle * 3.1415926 / 180.0f) * LASER_SPEED;

    sf::Vector2f position = shape.getPosition();
    sf::Vector2f nextPosition = position + sf::Vector2f(dx, dy);

    // Проверка столкновения с зеркалом
    for (auto& mirror : mirrors) {
        // Проход по пикселям лазера и проверка, нет ли столкновения с зеркалом
        for (int x = position.x; x < nextPosition.x; ++x) {
            for (int y = position.y; y < nextPosition.y; ++y) {
                if (mirror.shape.getGlobalBounds().contains(x, y)) {
                    // Обнаружено столкновение, отражение лазера
                    float theta = 2 * mirror.angle - angle;
                    float radians = theta * (3.1415926 / 180.0f);
                    float new_dx = std::cos(radians) * LASER_SPEED;
                    float new_dy = std::sin(radians) * LASER_SPEED;
                    shape.move(new_dx, new_dy);
                    angle = theta;
                    return;
                }
            }
        }
    }

    shape.move(dx, dy);

    // Проверка на выход лазера из окна игры
    if (nextPosition.x < 0 || nextPosition.x > WINDOW_WIDTH || nextPosition.y < 0 || nextPosition.y > WINDOW_HEIGHT) {
        alive = false;
    }

    // Проверка попадания в мишень
    for (auto it = targets.begin(); it != targets.end(); ++it) {
        if (shape.getGlobalBounds().intersects(it->shape.getGlobalBounds())) {
            // Уничтожение мишени
            it = targets.erase(it);
            if (it == targets.end()) break;
            alive = false; // Уничтожение лазера
            return;
        }
    }
}

void Laser::shoot(float angleDegrees) {
    alive = true;
    angle = angleDegrees;
    shape.setPosition(WINDOW_WIDTH / 2, 0); // Позиция источника лазера
}