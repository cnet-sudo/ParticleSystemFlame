


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Fire.h"

int main() {
    
    constexpr float WINDOW_WIDTH = 800.0f;  // Ширина окна
    constexpr float WINDOW_HEIGHT = 600.0f; // Высота окна

    // Создаем окно для отображения
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Realistic Fire Simulation");

    // Создаем объект Fire, передаем размеры окна
    Fire fire(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Переменная для хранения времени между кадрами
    sf::Clock clock;

    // Создание звукового буфера и загрузка аудиофайла
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("gorenie.wav"))  // Поддерживаемые форматы: WAV, OGG
    {
        return -1; // Обработка ошибки загрузки
    }

    // Создание звукового объекта и настройка параметров
    sf::Sound fireSound;
    fireSound.setBuffer(buffer);
    fireSound.setLoop(true);    // Бесконечное повторение
    fireSound.setVolume(70);    // Уровень громкости (0-100)
    fireSound.setPitch(0.9f);   // Небольшое снижение тона для реалистичности

    // Запуск воспроизведения
    fireSound.play();



    // Главный цикл программы
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();  // Закрытие окна
        }

        // Расчет дельта времени
        float deltaTime = clock.restart().asSeconds();

        fire.update(deltaTime*75);  // Обновляем состояние огня с учетом дельта времени

        window.clear();           // Очищаем экран
        window.draw(fire);        // Отрисовываем огонь
        window.display();         // Отображаем изменения на экране
    }

    return 0;
}

