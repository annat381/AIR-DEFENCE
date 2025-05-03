#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;



class Projectile
{
public:
    double x;
    double y;
    double v;
    double vx;
    double vy;
    double k = 0.05;
    bool visible;
    Texture textureProjectile;
    Sprite spriteProjectile;

    Projectile(double angle)
    {
        visible = true;
        v = 60;
        x = 35;
        y = 1040;
        vx = v * std::cos(angle * 3.14159 / 180);
        vy = -1 * v * std::sin(angle * 3.14159 / 180);
        textureProjectile.loadFromFile("./images/yellow.jpg");
        spriteProjectile.setTexture(textureProjectile);
        spriteProjectile.setTextureRect(IntRect(0, 0, 5, 5));
        spriteProjectile.setPosition(x, y);
    }

    Projectile()
    {

    }

    void upd(double t)
    {
        double sn = - vy / v;
        double cs = vx / v;
        v = v - k * v * v * t;
        vx = v * cs;
        vy += k * v * v * t * sn + 0.05;
        spriteProjectile.move(vx, vy);
        x += vx;
        y += vy;
    }

    void upd()
    {
        vy += 0.05;
        spriteProjectile.move(vx, vy);
    }

    ~Projectile() {}
};
