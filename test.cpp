#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main() {
    // �������� ����
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sound Example");

    // �������� ��������� ������
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("shot.wav")) { // ���� � ������ ��������� �����
        return -1; // ��������� ������
    }

    // �������� ������� �����
    sf::Sound shotSound;
    shotSound.setBuffer(buffer);

    // �������� ����
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // �������� ������� ������� ��� ��������
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) { // ������� ��� ������� �������
                    shotSound.play();
                }
            }
        }

        // ������� ���� � ���������
        window.clear();
        window.display();
    }

    return 0;
}
