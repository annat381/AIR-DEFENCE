#include <cmath>
#include <vector>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("./audio/cannon/shot.wav"))
    {
        return -1;
    }
    sf::Sound shotSound;
    shotSound.setBuffer(buffer);

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

    std::vector<Projectile> prj = {};

    auto last_shot = std::chrono::high_resolution_clock::now();

    while (window.isOpen())
	{
	    auto t1 = std::chrono::high_resolution_clock::now();
	    auto current_time = std::chrono::high_resolution_clock::now();

	    sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

		if (Keyboard::isKeyPressed(Keyboard::Space))
        {
            std::chrono::duration<double> duration_btw_shots = current_time - last_shot;
            double time_btw_shots = duration_btw_shots.count();

            if (time_btw_shots > 3)
            {
                shotSound.play();
                Projectile tst1(45);
                prj.push_back(tst1);
                last_shot = std::chrono::high_resolution_clock::now();
            }
        }

        window.clear();
        window.draw(spriteBackground);

        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = t2 - t1;
        double dt = duration.count();

        if (prj.size() > 0)
        {
            for (int i = 0; i < prj.size(); i++)
            {
                window.draw(prj[i].spriteProjectile);
                prj[i].upd(dt);
            }
        }

        window.display();
	}
}
