#include <SFML/Graphics.hpp>
#include <cmath>
using namespace sf;

const int L_JU87 = 1;
const int H_JU87 = 1;


double get_y(double x, double dx, double cx, double cy)
{
    x *= cx * 2 * 3.1415 / 1920;
    x += dx;

    double result = cy * std::cos(x) + 500;
    return result;
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
        x -= vx;
        y = get_y(x, dx, cx, cy);
        spriteJU87.setPosition(x, y);
    }
};
