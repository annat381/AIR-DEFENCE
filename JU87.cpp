#include <SFML/Graphics.hpp>
#include <cmath>
using namespace sf;

const int L_JU87 = 85;
const int H_JU87 = 36;


double get_y(double x, double dx, double cx, double cy)
{
    x *= cx * 3.1415 / 1920;
    x += dx;

    double result = cy * std::cos(x) + 700;
    return result;
}

double get_angle(double x, double dx, double cx, double cy)
{
    x *= cx * 3.1415 / 1920;
    x += dx;
    double arctg = std::atan(-1 * std::sin(x));
    arctg *= 90 / 3.1415;

    if (arctg < 0)
    {
        return (360 + arctg);
    }
    return arctg;
}


class JU87
{
public:
    double x;
    double y;
    double vx;
    double cx;
    double cy;
    double dx;
    bool visible;
    Texture textureJU87;
    Sprite spriteJU87;

    JU87()
    {

    }

    ~JU87()
    {

    }

    void upd()
    {
        x += vx;
        y = get_y(x, dx, cx, cy);
        spriteJU87.setPosition(x, y);
        spriteJU87.setRotation(get_angle(x, dx, cx, cy));
    }
};
