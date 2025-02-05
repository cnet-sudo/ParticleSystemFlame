

#include "Fire.h"

// ����������� ������, �������������� ��������� ��������� ����� � �������������
Fire::Fire(float width, float height)
    : randomEngine(std::random_device{}()),             // �������������� ��������� ��������� �����
    velocityDist(1.0f, 5.0f),                           // �������� �������� �� 1 �� 5
    lifespanDist(0.2f, 1.0f),                           // �������� ����������������� ����� �� 0.8 �� 1
    xPositionDist(0, static_cast<int>(width))           // �������� ��� ������� �� ��� X
{
    // ���������� ��������� ����
    for (int i = 0; i < SPARK_COUNT; ++i) {
        createSpark();  // ������� 100 ����
    }
}

// ����� ���������� ��������� ����: ��������, ��������� �������� � ����� ����
void Fire::update(float deltaTime) {
    // ��������� ������ �����
    for (auto& spark : sparks) {
        // ������� ����� ����� �� ��� Y
        spark.shape.move(0, -spark.velocity * deltaTime);

        // ��������� ����������������� ����� �����
        spark.lifespan -= 0.01f* deltaTime;

        // ������������ ����� � ����������� �� �� ����������������� �����
        float scale = spark.lifespan;
        spark.shape.setScale(scale, scale);

        // ��������� ���� ����� �� ������ ���������� ����������������� �����
        sf::Color color = sf::Color::Yellow;
        color.r = static_cast<sf::Uint8>(255 * spark.lifespan);  // ���� ���������� ����� ����������� � ����������� �����
        color.g = static_cast<sf::Uint8>(100 * spark.lifespan);
        color.b = static_cast<sf::Uint8>(0);
        color.a = static_cast<sf::Uint8>(255 * spark.lifespan); // ������������ ���� �����������

        // ��������� ����������� ����
        spark.shape.setFillColor(color);

        // ���� ����������������� ����� ����� �������, ������� ����� �����
        if (spark.lifespan <= 0) {
            spark.shape.setPosition(xPositionDist(randomEngine), WINDOW_HEIGHT);
            spark.lifespan = lifespanDist(randomEngine);  // ����� ������ ����������������� �����
        }
    }
}

// ����� �������� ����� ����� � ���������� �����������
void Fire::createSpark() {
    Spark spark;
    spark.shape = sf::CircleShape(SPARK_RADIUS);  // ������ �����
    spark.shape.setFillColor(sf::Color::Yellow);  // ��������� ���� � ������
    spark.shape.setPosition(xPositionDist(randomEngine), WINDOW_HEIGHT);  // ��������� ������� �� ������ ������� ������
    spark.velocity = velocityDist(randomEngine);  // ��������� ��������
    spark.lifespan = lifespanDist(randomEngine);  // ��������� ����������������� �����
    sparks.push_back(spark);                      // ��������� ����� � ������
}

// ��������������� ������ draw ��� ��������� ����
void Fire::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();     // ���������� ������������� (�����������, ��������������� � �.�.)
    for (const auto& spark : sparks) {
        target.draw(spark.shape, states);   // ������������ ������ �����
    }
}
