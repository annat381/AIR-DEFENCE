#include <cmath>
#include <vector>
#include <random>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Projectile.cpp"
#include "B17.cpp"
#include "JU87.cpp"
#include "rnd_int.cpp"
#include "Explosion.cpp"
using namespace sf;

//data about screen
const int HEIGHT = 1080;
const int WIDTH = 1920;
const int FRAMERATE_LIMIT = 60;

//data about cannon
const int BARREL_L = 200;
const int BARREL_H = 15;
const double BARREL_ROTATING_SPEED = 0.35;
double RELOAD_TIME = 0.5; //don't make const
const int MAX_AMOUNT_OF_PROJECTILES = 50;

//data about B17
const int B17_MAX_VX = 10;
const int B17_MIN_VX = 7;
const int B17_ABS_MAX_OF_VY = 0;
const int B17_H_MIN = 100;
const int B17_H_MAX = 300;
const int MAX_AMOUNT_OF_B17 = 7;
const double MIN_DELAY_BETWEEN_B17 = 1;
const double B17_SPAWN_PROBABILITY = 0.005;

//data about JU87
const int JU87_MIN_VX = 5;
const int JU87_MAX_VX = 7;
const int MAX_AMOUNT_OF_JU87 = 7;
const double JU87_SPAWN_PROBABILITY = 0.005;
const double MIN_DELAY_BETWEEN_JU87 = 1;

//data about explosions
const int MAX_AMOUNT_OF_EXPLOSIONS = 10;
int counter_of_explosions = 0; //must be global
int number_of_explosions = 0; //must be global

Explosion arr_explosions[MAX_AMOUNT_OF_EXPLOSIONS]; //must be global



bool do_spawn_B17()
{
    int number = rnd_int(1, 10000);
    return number > (10000 * (1 - B17_SPAWN_PROBABILITY));
}

bool do_spawn_JU87()
{
    int number = rnd_int(1, 10000);
    return number > (10000 * (1 - JU87_SPAWN_PROBABILITY));
}

void create_explosion(int x, int y)
{
    arr_explosions[counter_of_explosions].counter = 1;
    arr_explosions[counter_of_explosions].visible = true;
    arr_explosions[counter_of_explosions].textureExplosion.loadFromFile("./images/explosion/explosion1.png");
    arr_explosions[counter_of_explosions].spriteExplosion.setTexture(arr_explosions[counter_of_explosions].textureExplosion);
    arr_explosions[counter_of_explosions].spriteExplosion.setTextureRect(IntRect(0, 0, L_EXPLOSION, H_EXPLOSION));
    arr_explosions[counter_of_explosions].spriteExplosion.setPosition(x, y);

    counter_of_explosions += 1;
    if (counter_of_explosions == MAX_AMOUNT_OF_EXPLOSIONS)
    {
        counter_of_explosions = 0;
    }
    if (number_of_explosions < MAX_AMOUNT_OF_EXPLOSIONS)
    {
        number_of_explosions += 1;
    }
}



Clock last_shot;
Clock last_B17;
Clock last_JU87;
Clock current_time;



int main()
{
    //static array of projectiles
    Projectile arr_projectiles[MAX_AMOUNT_OF_PROJECTILES];

    //static array of B17
    B17 arr_B17[MAX_AMOUNT_OF_B17];

    //static array of JU87
    JU87 arr_JU87[MAX_AMOUNT_OF_JU87];

    //shot sound
    SoundBuffer buffer1;
    buffer1.loadFromFile("./audio/cannon/shot.wav");
    Sound shotSound;
    shotSound.setBuffer(buffer1);

    //explosion sound
    SoundBuffer buffer2;
    buffer2.loadFromFile("./audio/cannon/explosion.wav");
    Sound explosionSound;
    explosionSound.setBuffer(buffer2);

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

    int counter_projectiles = 0;
    int number_of_shots = 0;

    int counter_B17 = 0;
    int number_of_B17 = 0;

    int counter_JU87 = 0;
    int number_of_JU87 = 0;



    while (window.isOpen())
	{
        //event handler
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
                arr_projectiles[counter_projectiles] = p;

                if (counter_projectiles < (MAX_AMOUNT_OF_PROJECTILES - 1))
                {
                    counter_projectiles += 1;
                }
                else
                {
                    counter_projectiles = 0;
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

        if (Keyboard::isKeyPressed(Keyboard::S) and spriteBarrel.getRotation() >= 280)
        {
            spriteBarrel.rotate(-BARREL_ROTATING_SPEED);
            if (spriteBarrel.getRotation() < 280)
            {
                spriteBarrel.setRotation(280);
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
                        RELOAD_TIME = 0.02;
                    }
                }
            }
        }

        //rendering background
        //window.clear();
        window.draw(spriteBackground);

        //get time for projectiles
        double time_for_projectile = current_time.getElapsedTime().asMicroseconds();
        time_for_projectile = time_for_projectile / 1000000;
        current_time.restart();

        //updating and rendering projectiles
        if (number_of_shots > 0)
        {
            for (int i = 0; i < number_of_shots; i++)
            {
                if (arr_projectiles[i].visible)
                {
                    window.draw(arr_projectiles[i].spriteProjectile);
                    arr_projectiles[i].upd(time_for_projectile);
                }
            }
        }

        //spawning B17
        double time_for_B17 = last_B17.getElapsedTime().asMicroseconds();
        time_for_B17 /= 1000000;

        if (do_spawn_B17() and time_for_B17 > MIN_DELAY_BETWEEN_B17)
        {
            if (counter_B17 <= MAX_AMOUNT_OF_B17)
            {
                arr_B17[counter_B17].textureB17.loadFromFile("./images/planes/b17.png");
                arr_B17[counter_B17].spriteB17.setTexture(arr_B17[counter_B17].textureB17);
                arr_B17[counter_B17].spriteB17.setTextureRect(IntRect(0, 0, L_B17, H_B17));
            }
            arr_B17[counter_B17].visible = true;
            arr_B17[counter_B17].x = 1920;
            arr_B17[counter_B17].y = rnd_int(B17_H_MIN, B17_H_MAX);
            arr_B17[counter_B17].spriteB17.setPosition(arr_B17[counter_B17].x, arr_B17[counter_B17].y);
            arr_B17[counter_B17].vx = rnd_int(-B17_MAX_VX, -B17_MIN_VX);
            arr_B17[counter_B17].vy = rnd_int(-B17_ABS_MAX_OF_VY, B17_ABS_MAX_OF_VY);

            counter_B17 += 1;
            if (counter_B17 == MAX_AMOUNT_OF_B17)
            {
                counter_B17 = 0;
            }
            if (number_of_B17 < MAX_AMOUNT_OF_B17)
            {
                number_of_B17 += 1;
            }

            last_B17.restart();
        }

        //spawning JU87
        double time_for_JU87 = last_JU87.getElapsedTime().asMicroseconds();
        time_for_JU87 /= 1000000;

        if (do_spawn_JU87() and time_for_JU87 > MIN_DELAY_BETWEEN_JU87)
        {
            if (counter_JU87 <= MAX_AMOUNT_OF_B17)
            {
                arr_JU87[counter_JU87].textureJU87.loadFromFile("./images/planes/ju87.png");
                arr_JU87[counter_JU87].spriteJU87.setTexture(arr_JU87[counter_JU87].textureJU87);
                arr_JU87[counter_JU87].spriteJU87.setTextureRect(IntRect(0, 0, L_JU87, H_JU87));
            }
            arr_JU87[counter_JU87].visible = true;
            arr_JU87[counter_JU87].dx = 3.1415 / 16 * rnd_int(0, 32);
            arr_JU87[counter_JU87].cx = 1;//will be changed
            arr_JU87[counter_JU87].cy = rnd_int(100, 200);
            arr_JU87[counter_JU87].x = 1920;
            arr_JU87[counter_JU87].y = get_y(arr_JU87[counter_JU87].x, arr_JU87[counter_JU87].dx, arr_JU87[counter_JU87].cx, arr_JU87[counter_JU87].cy);
            arr_JU87[counter_JU87].spriteJU87.setPosition(arr_JU87[counter_JU87].x, arr_JU87[counter_JU87].y);
            arr_JU87[counter_JU87].vx = rnd_int(-JU87_MAX_VX, -JU87_MIN_VX);

            counter_JU87 += 1;
            if (counter_JU87 == MAX_AMOUNT_OF_JU87)
            {
                counter_JU87 = 0;
            }
            if (number_of_JU87 < MAX_AMOUNT_OF_JU87)
            {
                number_of_JU87 += 1;
            }

            last_JU87.restart();
        }

        //updating and rendering B17, checking for hits, creating explosions
        for (int i = 0; i < number_of_B17; i++)
        {
            if (arr_B17[i].visible)
            {
                for (int j = 0; j < number_of_shots; j++)
                {
                    if (arr_B17[i].spriteB17.getGlobalBounds().intersects(arr_projectiles[j].spriteProjectile.getGlobalBounds()) and arr_projectiles[j].visible)
                    {
                        explosionSound.play();
                        arr_B17[i].visible = false;
                        arr_projectiles[j].visible = false;
                        Vector2f p = arr_projectiles[j].spriteProjectile.getPosition();
                        int x = (int) p.x;
                        x -= L_EXPLOSION / 2;
                        int y = (int) p.y;
                        y -= H_EXPLOSION / 2;
                        create_explosion(x, y);
                    }
                }

                window.draw(arr_B17[i].spriteB17);
                arr_B17[i].upd();
            }
        }

        //updating and rendering JU87, checking for hits, creating explosions
        for (int i = 0; i < number_of_JU87; i++)
        {
            if (arr_JU87[i].visible)
            {
                for (int j = 0; j < number_of_shots; j++)
                {
                    if (arr_JU87[i].spriteJU87.getGlobalBounds().intersects(arr_projectiles[j].spriteProjectile.getGlobalBounds()) and arr_projectiles[j].visible)
                    {
                        explosionSound.play();
                        arr_JU87[i].visible = false;
                        arr_projectiles[j].visible = false;
                        Vector2f p = arr_projectiles[j].spriteProjectile.getPosition();
                        int x = (int) p.x;
                        x -= L_EXPLOSION / 2;
                        int y = (int) p.y;
                        y -= H_EXPLOSION / 2;
                        create_explosion(x, y);
                    }
                }

                window.draw(arr_JU87[i].spriteJU87);
                arr_JU87[i].upd();
            }
        }

        //updating and rendering explosions
        for (int i = 0; i < number_of_explosions; i++)
        {
            if (arr_explosions[i].visible)
            {
                window.draw(arr_explosions[i].spriteExplosion);
                arr_explosions[i].upd();
            }
        }

        //rendering cannon
        window.draw(spriteBarrel);
        window.display();
	}
}
