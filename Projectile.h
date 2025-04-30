#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Projectile
{
public:
    int x;
    int y;
    double v;
    double vx;
    double vy;
    double k = 0.1;
    Texture textureProjectile;
    Sprite spriteProjectile;

    Projectile(double angle);
    Projectile();
    void upd(double t);
    void upd();
};
