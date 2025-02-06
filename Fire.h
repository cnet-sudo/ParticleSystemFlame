


#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

// Класс Fire моделирует огонь с помощью искр
class Fire : public sf::Drawable, public sf::Transformable {
public:
    // Конструктор класса. Принимает ширину и высоту окна.
    Fire(float width, float height);

    // Метод обновления состояния огня (движение искр, изменение их масштаба, цвет и т.д.)
    void update(float deltaTime);

private:
    // Структура, представляющая отдельную искру.
    struct Spark {
        sf::CircleShape shape;  // Фигура для рисования искры
        float velocity;         // Скорость искры
        float lifespan;         // Продолжительность жизни искры (время, через которое она исчезнет)
    };

    // Вектор для хранения всех искр
    std::vector<Spark> sparks;

    // Модернизированный генератор случайных чисел и распределения для разных параметров искры
    std::mt19937 randomEngine;  // Генератор случайных чисел
    std::uniform_real_distribution<float> velocityDist;    // Распределение для скорости
    std::uniform_real_distribution<float> lifespanDist;    // Распределение для продолжительности жизни
    std::uniform_int_distribution<int> xPositionDist;      // Распределение для начальной позиции по оси X

    // Константы для параметров искры и окна
    static constexpr float SPARK_RADIUS = 6.0f;             // Радиус искры
    static constexpr int SPARK_COUNT = 30000;                // Количество искр
    int WINDOW_HEIGHT;                                      // Высота окна

    // Метод для создания новой искры
    void createSpark();

    // Переопределение метода draw из sf::Drawable для отрисовки объекта
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

