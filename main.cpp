#include <SFML/Graphics.hpp>
#include "plane.h"
using namespace sf;

const int HEIGHT = 1080;
const int WIDTH = 1920;



int main()
{
    RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "h", sf::Style::Fullscreen);

    Texture textureBackground;
    textureBackground.loadFromFile("whitescreen.jpg");
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setTextureRect(IntRect(0, 0, 1920, 1080));
    spriteBackground.setPosition(0, 0);

    Texture textureTest;
    textureTest.loadFromFile("arrow.jpg");
    Sprite spriteTest;
    spriteTest.setTexture(textureTest);
    spriteTest.setTextureRect(IntRect(0, 0, 100, 100));
    spriteTest.setPosition(200, 200);

    while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
        //if (Keyboard::isKeyPressed(Keyboard::F)) { spriteTest.move(1, 0); }
		//if (Keyboard::isKeyPressed(Keyboard::S)) { spriteTest.move(-1, 0); }
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { window.close();}
		/*if (Keyboard::isKeyPressed(Keyboard::Up)) { spriteHare.move(0, -1); }
		if (Keyboard::isKeyPressed(Keyboard::Down)) { spriteHare.move(0, 1); }*/
        spriteTest.move(10, 0);

        window.clear();
        window.draw(spriteBackground);
        window.draw(spriteTest);
        window.display();
	}
}
