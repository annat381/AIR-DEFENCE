#include <cmath>
#include <vector>
#include <random>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "B17.cpp"
#include "rnd_int.cpp"
using namespace sf;

//data about screen
const int HEIGHT = 1080;
const int WIDTH = 1920;
const int FRAMERATE_LIMIT = 60;

//data about cannon
const int BARREL_L = 200;
const int BARREL_H = 15;
const double BARREL_ROTATING_SPEED = 0.35;
double RELOAD_TIME = 3; //don't make const
const int MAX_AMOUNT_OF_PROJECTILES = 400;

//data about B17
const int B17_MAX_VX = 10;
const int B17_MIN_VX = 7;
const int B17_ABS_MAX_OF_VY = 0;
const int B17_H_MIN = 100;
const int B17_H_MAX = 300;



Clock last_shot;
Clock current_time;



int main()
{
    //static array of projectiles
    Projectile arr_projectiles[MAX_AMOUNT_OF_PROJECTILES];

    //static array of B17
    B17 arr_B17[1];
    B17 plane(rnd_int(-B17_MAX_VX, -B17_MIN_VX), rnd_int(-B17_ABS_MAX_OF_VY, B17_ABS_MAX_OF_VY), rnd_int(B17_H_MIN, B17_H_MAX));
    arr_B17[0] = plane;

    //shot sound
    SoundBuffer buffer;
    buffer.loadFromFile("./audio/cannon/shot.wav");
    Sound shotSound;
    shotSound.setBuffer(buffer);

    //opening window
    RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "h", sf::Style::Fullscreen);
    window.setFramerateLimit(FRAMERATE_LIMIT);

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
    spriteBarrel.rotate(315);

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
            time_btw_shots /= 1000000;

            if (time_btw_shots > RELOAD_TIME)
            {
                shotSound.play();

                Projectile p(-spriteBarrel.getRotation());
                arr_projectiles[counter] = p;

                if (counter < (MAX_AMOUNT_OF_PROJECTILES - 1))
                {
                    counter += 1;
                }
                else
                {
                    counter = 0;
                }

                last_shot.restart();

                if (number_of_shots < MAX_AMOUNT_OF_PROJECTILES)
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
            spriteBarrel.rotate(-BARREL_ROTATING_SPEED);
            if (spriteBarrel.getRotation() < 270)
            {
                spriteBarrel.setRotation(270);
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::F) and spriteBarrel.getRotation() <= 359.5)
        {
            spriteBarrel.rotate(BARREL_ROTATING_SPEED);
            if (spriteBarrel.getRotation() > 359.5)
            {
                spriteBarrel.setRotation(359.5);
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::H))
        {
            if (Keyboard::isKeyPressed(Keyboard::E))
            {
                if (Keyboard::isKeyPressed(Keyboard::L))
                {
                    if (Keyboard::isKeyPressed(Keyboard::P))
                    {
                        RELOAD_TIME = 0.01;
                    }
                }
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
                if (arr_projectiles[i].visible)
                {
                    window.draw(arr_projectiles[i].spriteProjectile);
                    arr_projectiles[i].upd(time_for_upd);
                }
            }
        }

        window.draw(arr_B17[0].spriteB17);
        arr_B17[0].spriteB17.move(arr_B17[0].vx, arr_B17[0].vy);

        window.draw(spriteBarrel);
        window.display();
	}
}
