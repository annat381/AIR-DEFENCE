#include <SFML/Graphics.hpp>
#include <chrono>
using namespace sf;

class Shell
{
public:
    int damage;
    int x;
    int y;
    double vx;
    double vy;
    Texture textureShell;
    Sprite spriteShell;

    void upd(double t1, double t2)
    {
        vv = vx * vx + vy * vy;
    }
};
