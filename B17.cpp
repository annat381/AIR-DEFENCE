#include <SFML/Graphics.hpp>
using namespace sf;

const int L_B17 = 166;
const int H_B17 = 50;



class B17
{
public:
    double x;
    double y;
    double vx;
    double vy;
    bool visible;
    Texture textureB17;
    Sprite spriteB17;

    /*B17(int v_x, int v_y, int h)
    {
        textureB17.loadFromFile("./images/planes/b17.png");
        spriteB17.setTexture(textureB17);
        spriteB17.setTextureRect(IntRect(0, 0, L_B17, H_B17));
        spriteB17.setPosition(1920, h);
        vx = v_x;
        vy = v_y;
    }*/

    B17()
    {

    }

    void upd()
    {
        spriteB17.move(vx, vy);
        x += vx;
        y += vy;
    }

    ~B17()
    {

    }
};
