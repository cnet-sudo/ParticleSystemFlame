

#include "Fire.h"

// Конструктор класса, инициализирует генератор случайных чисел и распределения
Fire::Fire(float width, float height)
    : randomEngine(std::random_device{}()),             // Инициализируем генератор случайных чисел
    velocityDist(1.0f, 5.0f),                           // Диапазон скорости от 1 до 5
    lifespanDist(0.2f, 1.0f),                           // Диапазон продолжительности жизни от 0.8 до 1
    xPositionDist(0, static_cast<int>(width))           // Диапазон для позиции по оси X
{
    // Заполнение начальных искр
    for (int i = 0; i < SPARK_COUNT; ++i) {
        createSpark();  // Создаем 100 искр
    }
}

// Метод обновления состояния огня: движение, изменение размеров и цвета искр
void Fire::update(float deltaTime) {
    // Обработка каждой искры
    for (auto& spark : sparks) {
        // Двигаем искры вверх по оси Y
        spark.shape.move(0, -spark.velocity * deltaTime);

        // Уменьшаем продолжительность жизни искры
        spark.lifespan -= 0.01f* deltaTime;

        // Масштабируем искру в зависимости от ее продолжительности жизни
        float scale = spark.lifespan;
        spark.shape.setScale(scale, scale);

        // Вычисляем цвет искры на основе оставшейся продолжительности жизни
        sf::Color color = sf::Color::Yellow;
        color.r = static_cast<sf::Uint8>(255 * spark.lifespan);  // Цвет становится менее интенсивным с уменьшением жизни
        color.g = static_cast<sf::Uint8>(100 * spark.lifespan);
        color.b = static_cast<sf::Uint8>(0);
        color.a = static_cast<sf::Uint8>(255 * spark.lifespan); // Прозрачность тоже уменьшается

        // Применяем вычисленный цвет
        spark.shape.setFillColor(color);

        // Если продолжительность жизни искры истекла, создаем новую искру
        if (spark.lifespan <= 0) {
            spark.shape.setPosition(xPositionDist(randomEngine), WINDOW_HEIGHT);
            spark.lifespan = lifespanDist(randomEngine);  // Снова задаем продолжительность жизни
        }
    }
}

// Метод создания новой искры с случайными параметрами
void Fire::createSpark() {
    Spark spark;
    spark.shape = sf::CircleShape(SPARK_RADIUS);  // Радиус искры
    spark.shape.setFillColor(sf::Color::Yellow);  // Начальный цвет — желтый
    spark.shape.setPosition(xPositionDist(randomEngine), WINDOW_HEIGHT);  // Начальная позиция на нижней границе экрана
    spark.velocity = velocityDist(randomEngine);  // Случайная скорость
    spark.lifespan = lifespanDist(randomEngine);  // Случайная продолжительность жизни
    sparks.push_back(spark);                      // Добавляем искру в вектор
}

// Переопределение метода draw для отрисовки искр
void Fire::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();     // Применение трансформации (перемещения, масштабирования и т.д.)
    for (const auto& spark : sparks) {
        target.draw(spark.shape, states);   // Отрисовываем каждую искру
    }
}
