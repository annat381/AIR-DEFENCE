#include <SFML/Graphics.hpp>
#include "Projectile.cpp"
using namespace sf;

const int L_B17 = 176;
const int H_B17 = 136;



class B17
{
public:
    int vx;
    int vy;
    Texture textureB17;
    Sprite spriteB17;

    B17(int v_x, int v_y, int h)
    {
        textureB17.loadFromFile("./images/planes/b17.png");
        spriteB17.setTexture(textureB17);
        spriteB17.setTextureRect(IntRect(0, 0, L_B17, H_B17));
        spriteB17.setPosition(1920, h);
        vx = v_x;
        vy = v_y;
    }

    B17()
    {

    }

    void upd()
    {
        spriteB17.move(vx, vy);
    }

    bool is_overlapping(Projectile p)
    {
        return true;
    }

    ~B17()
    {

    }
};
