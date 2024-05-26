#include <SFML/Graphics.hpp>
#include "Mirror.h"
#include "Target.h"
#include "Laser.h"
#include "Utilities.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <random>

const int NUM_MIRRORS = 25;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ricochet Game");

    std::vector<Mirror> mirrors;
    std::vector<Target> targets;
    Laser laser;

    // Генерация зеркал с минимальной дистанцией между ними
    float minDistance = MIRROR_SIZE * 2; // Минимальная дистанция между зеркалами
    for (int i = 0; i < NUM_MIRRORS; ++i) {
        float x, y;
        do {
            x = randomFloat(0, WINDOW_WIDTH);
            y = randomFloat(0, WINDOW_HEIGHT);
        } while (isTooClose(mirrors, sf::Vector2f(x, y), minDistance));
        float angle = randomFloat(0, 360);
        mirrors.push_back(Mirror(x, y, angle));
    }

    // Генерация мишеней в нижней части экрана
    for (int i = 0; i < 3; ++i) {
        float x = randomFloat(0, WINDOW_WIDTH);
        float y = randomFloat(WINDOW_HEIGHT / 2, WINDOW_HEIGHT);
        targets.push_back(Target(x, y));
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    // Поворот зеркала, при нажатии кнопки пробела
                    for (auto& mirror : mirrors) {
                        mirror.rotateClockwise();
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Получение положение щелчка мыши относительно центра окна
                float dx = event.mouseButton.x - WINDOW_WIDTH / 2;
                float dy = event.mouseButton.y - 0;
                float angleDegrees = std::atan2(dy, dx) * 180.0f / 3.1415926f;
                laser.shoot(angleDegrees);
            }
        }

        window.clear();

        // Отрисовка зеркал
        for (const auto& mirror : mirrors) {
            window.draw(mirror.shape);
        }

        // Отрисовка мишеней
        for (const auto& target : targets) {
            window.draw(target.shape);
        }

        // Обновлене и отрисовка лазера
        if (laser.alive) {
            laser.update(mirrors, targets);
            window.draw(laser.shape);
        }

        window.display();
    }

    return 0;
}