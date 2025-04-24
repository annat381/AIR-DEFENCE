#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>
#include "B17.cpp"
#include "Projectile.cpp"
using namespace sf;

const int MAX_AMOUNT_OF_OBJECTS = 1000;

const int HEIGHT = 1080;
const int WIDTH = 1920;

//const int L_JU87 = 90;
//const int H_JU87 = 51;
//const int L_B17 = 176;
//const int H_B17 = 136;




int main()
{
    RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "h", sf::Style::Fullscreen);

    Texture textureBackground;
    textureBackground.loadFromFile("./images/landscape/nightsky.jpg");
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setTextureRect(IntRect(0, 0, WIDTH, HEIGHT));
    spriteBackground.setPosition(0, 0);

    /*Texture textureTest;
    textureTest.loadFromFile("./images/b17.png");
    Sprite spriteTest;
    spriteTest.setTexture(textureTest);
    spriteTest.setTextureRect(IntRect(0, 0, 176, 136));
    spriteTest.setPosition(1000, 500);*/

    B17 test;

    std::vector<B17> planesB17 = {test};

    Projectile shell(80);

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
        //spriteTest.move(-10, 0);

        window.clear();
        window.draw(spriteBackground);

        for (unsigned long int i = 0; i < planesB17.size(); i++)
        {
            window.draw(planesB17[i].spriteB17);
        }

        window.draw(shell.spriteProjectile);
        shell.upd();

        window.display();
	}
}
