#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "B17.cpp"
#include "Projectile.cpp"
using namespace sf;

const int HEIGHT = 1080;
const int WIDTH = 1920;

const int BARREL_L = 200;
const int BARREL_H = 15;

const double reload_time = 0.25; //don't make too small; it's minimal time between shots
const int max_amount_of_projectiles = 50; //don't make too big or small; that number shows how much projectiles can be drawn, oldest are replaced by new

//const int L_JU87 = 90;
//const int H_JU87 = 51;
//const int L_B17 = 176;
//const int H_B17 = 136;

Clock last_shot;
Clock current_time;



int main()
{
    //static array of projectiles
    Projectile arr[max_amount_of_projectiles];

    //shot sound
    SoundBuffer buffer;
    buffer.loadFromFile("./audio/cannon/shot.wav");
    Sound shotSound;
    shotSound.setBuffer(buffer);

    //opening window
    RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "h", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    //creating background
    Texture textureBackground;
    textureBackground.loadFromFile("./images/landscape/nightsky.jpg");
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setTextureRect(IntRect(0, 0, WIDTH, HEIGHT));
    spriteBackground.setPosition(0, 0);

    //creating barrel
    Texture textureBarrel;
    textureBarrel.loadFromFile("./images/cannon/no_dots1.png");
    Sprite spriteBarrel;
    spriteBarrel.setTexture(textureBarrel);
    spriteBarrel.setTextureRect(IntRect(0, 0, BARREL_L, BARREL_H));
    spriteBarrel.setPosition(30, 1040);
    spriteBarrel.rotate(359.5);

    int counter = 0;
    int number_of_shots = 0;

    while (window.isOpen())
	{

	    sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Space))
        {
            double time_btw_shots = last_shot.getElapsedTime().asMicroseconds();
            time_btw_shots = time_btw_shots / 1000000;

            if (time_btw_shots > reload_time)
            {
                shotSound.play();

                Projectile p(-spriteBarrel.getRotation());
                arr[counter] = p;

                if (counter < (max_amount_of_projectiles - 1))
                {
                    counter += 1;
                }
                else
                {
                    counter = 0;
                }

                last_shot.restart();

                if (number_of_shots < max_amount_of_projectiles)
                {
                    number_of_shots += 1;
                }
            }
        }

		if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::S) and spriteBarrel.getRotation() >= 270)
        {
            spriteBarrel.rotate(-0.25);
            if (spriteBarrel.getRotation() < 270)
            {
                spriteBarrel.setRotation(270);
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::F) and spriteBarrel.getRotation() <= 359.5)
        {
            spriteBarrel.rotate(0.25);
            if (spriteBarrel.getRotation() > 359.5)
            {
                spriteBarrel.setRotation(359.5);
            }
        }

        window.clear();
        window.draw(spriteBackground);

        double time_for_upd = current_time.getElapsedTime().asMicroseconds();
        time_for_upd = time_for_upd / 1000000;
        current_time.restart();

        if (number_of_shots > 0)
        {
            for (int i = 0; i < number_of_shots; i++)
            {
                window.draw(arr[i].spriteProjectile);
                arr[i].upd(time_for_upd);
            }
        }

        window.draw(spriteBarrel);
        window.display();
	}
}
