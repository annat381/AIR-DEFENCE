#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main() {
    // Создание окна
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sound Example");

    // Загрузка звукового буфера
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("shot.wav")) { // Путь к вашему звуковому файлу
        return -1; // Обработка ошибки
    }

    // Создание объекта звука
    sf::Sound shotSound;
    shotSound.setBuffer(buffer);

    // Основной цикл
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Проверка нажатия клавиши для выстрела
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) { // Выстрел при нажатии пробела
                    shotSound.play();
                }
            }
        }

        // Очистка окна и отрисовка
        window.clear();
        window.display();
    }

    return 0;
}
