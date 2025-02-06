


#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

// ����� Fire ���������� ����� � ������� ����
class Fire : public sf::Drawable, public sf::Transformable {
public:
    // ����������� ������. ��������� ������ � ������ ����.
    Fire(float width, float height);

    // ����� ���������� ��������� ���� (�������� ����, ��������� �� ��������, ���� � �.�.)
    void update(float deltaTime);

private:
    // ���������, �������������� ��������� �����.
    struct Spark {
        sf::CircleShape shape;  // ������ ��� ��������� �����
        float velocity;         // �������� �����
        float lifespan;         // ����������������� ����� ����� (�����, ����� ������� ��� ��������)
    };

    // ������ ��� �������� ���� ����
    std::vector<Spark> sparks;

    // ����������������� ��������� ��������� ����� � ������������� ��� ������ ���������� �����
    std::mt19937 randomEngine;  // ��������� ��������� �����
    std::uniform_real_distribution<float> velocityDist;    // ������������� ��� ��������
    std::uniform_real_distribution<float> lifespanDist;    // ������������� ��� ����������������� �����
    std::uniform_int_distribution<int> xPositionDist;      // ������������� ��� ��������� ������� �� ��� X

    // ��������� ��� ���������� ����� � ����
    static constexpr float SPARK_RADIUS = 6.0f;             // ������ �����
    static constexpr int SPARK_COUNT = 30000;                // ���������� ����
    int WINDOW_HEIGHT;                                      // ������ ����

    // ����� ��� �������� ����� �����
    void createSpark();

    // ��������������� ������ draw �� sf::Drawable ��� ��������� �������
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

