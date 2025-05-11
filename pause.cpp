#include "pause.hpp"
#include <SFML/Graphics.hpp>

void handle_pause(sf::RenderWindow& window, sf::Font& font) {
    sf::Text pauseText("ПАУЗА", font, 60);
    pauseText.setFillColor(sf::Color::Red);
    pauseText.setPosition(
        static_cast<float>(window.getSize().x / 2 - static_cast<int>(pauseText.getLocalBounds().width / 2)),
        static_cast<float>(window.getSize().y / 2 - static_cast<int>(pauseText.getLocalBounds().height / 2))
    );

    bool paused = true;
    sf::Clock pauseClock;
    pauseClock.restart();

    while (paused) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // выход из паузы, нажать Enter
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            paused = false;
        }

        //дефолтный выход через 5 секунд
        if (pauseClock.getElapsedTime().asSeconds() >= 5.0f) {
            paused = false;
        }

        //отрисовываем и очищаем экран паузы
        window.clear(sf::Color(30, 30, 30));
        window.draw(pauseText);
        window.display();
    }
}
