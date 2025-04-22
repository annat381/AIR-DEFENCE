#include <cmath>
#include <SFML/Graphics.hpp>
#include <chrono>
using namespace sf;

class projectile
{
public:
    int damage;
    int x;
    int y;
    double vx;
    double vy;
    double k;
    Texture textureShell;
    Sprite spriteShell;

    void spawn()
    {

    }

    void upd(double t1, double t2)
    {
        vv = vx.cmath::pow(2) + vy.cmath::pow(2);
        vx = vx - k * vv * (vx / vv.cmath::pow(0.5));
        vy = vy - k * vv * (vy / vv.cmath::pow(0.5));
        x += vx * (t2 - t1);
        y += vy * (t2 - t1);
    }
};
